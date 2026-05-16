/*
 * ====================================================================
 * FILE: GameEngine.cpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Core game engine implementation handling collision detection, gravity
 * physics, and game state management. Uses lambda expressions for
 * collision processing and dynamic_cast for RTTI-based type checking.
 * Manages platform regeneration and game-over conditions.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Lambda Expressions: Collision checking and game-over lambdas
 * - RTTI: dynamic_pointer_cast for runtime type identification
 * - Polymorphism: Calls virtual getDistance() on polymorphic Platform*
 * - Random Number Generation: mt19937 for random platform positioning
 * - Composition: Manages GameLoop and delegates to Doodler/Platform
 * - Physics Engine: Gravity simulation and collision response
 * ====================================================================
 */

#include "GameEngine.hpp"
#include "Enemy.hpp"

GameEngine::~GameEngine() {}

void GameEngine::checkCollision()
{
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());

    gameLoop.doodler->set_dy(gameLoop.doodler->get_dy() + 0.2f);
    gameLoop.doodler->setUpDownPosition();

    if (gameLoop.doodler->getPosition().y < DOODLER_HEIGHT) {    // I maintain my doodler at DOODLER_HEIGHT
        gameLoop.doodler->setPosition({gameLoop.doodler->getPosition().x, DOODLER_HEIGHT});
        
        for (auto& platform : gameLoop.platforms) { 
            platform->setPosition({platform->getPosition().x, platform->getPosition().y - gameLoop.doodler->get_dy()}); // vertical translation
            if (platform->getPosition().y > WINDOW_HEIGHT) {
                // Set new platform on the top    
                std::uniform_int_distribution<unsigned> x(0, WINDOW_WIDTH - platform->getTextureSize().x);	
                platform->setPosition({static_cast<float>(x(generator)), 0});

                if (std::shared_ptr<SlowPlatform> sp = std::dynamic_pointer_cast<SlowPlatform>(platform)) {
                    if (sp->getHasCollision() == true) {
                        sp->setHasCollision(false);
                    }
                }
            }
        }
        
        // Move enemies vertically along with screen scroll (only during active enemy waves)
        if (shouldShowEnemies()) {
            for (auto& enemy : gameLoop.enemies) {
                enemy->setPosition({enemy->getPosition().x, enemy->getPosition().y - gameLoop.doodler->get_dy()});
                if (enemy->getPosition().y > WINDOW_HEIGHT) {
                    enemy->setPosition({enemy->getPosition().x, -50});
                }
            }
        }
	}

    std::for_each(gameLoop.platforms.begin(), gameLoop.platforms.end(), processCollisionForEach);
    
    // Check collision with enemies (only during active enemy waves)
    if (shouldShowEnemies()) {
        std::for_each(gameLoop.enemies.begin(), gameLoop.enemies.end(),
            [this](const std::shared_ptr<Enemy>& enemy) -> void {
                manageEnemySound(enemy, soundManager);
                checkEnemyCollision(enemy);
            });
    } else {
        // Stop enemy sound if we're not in active enemy wave
        if (isEnemySoundPlaying && soundManager) {
            soundManager->stopSound("enemy");
            isEnemySoundPlaying = false;
        }
    } 
}

void GameEngine::processCollision(const std::shared_ptr<Platform>& platform)
{ 
    if (doesIntersect(platform)) {
        if (std::dynamic_pointer_cast<SlowPlatform>(platform)) {
            // Init statement for if - Feature of C++17
            if (std::shared_ptr<SlowPlatform> sp = std::dynamic_pointer_cast<SlowPlatform>(platform); sp->getHasCollision() == false) {
                gameLoop.doodler->set_dy(-static_cast<float>(platform->getDistance()));// Distance travelled when jumping on this platform
                sp->setHasCollision(true);
                SoundManager::getInstance()->playSound("jump");
            }
            // Note: I do not call setHasCollision if the doodler intersects a SlowPlatform that has "hasCollision" = true
            // because this means that the platform is not visible.
        } else {
            gameLoop.doodler->set_dy(-static_cast<float>(platform->getDistance()));
            SoundManager::getInstance()->playSound("jump");
        }
    }
}

bool GameEngine::doesIntersect(const std::shared_ptr<Platform>& platform) const
{
    if ((gameLoop.doodler->getPosition().x + DOODLER_RIGHT_BOUNDING_BOX > platform->getPosition().x)
        && (gameLoop.doodler->getPosition().x + DOODLER_LEFT_BOUNDING_BOX < platform->getPosition().x + platform->getTextureSize().x) 
        && (gameLoop.doodler->getPosition().y + DOODLER_BOTTOM_BOUNDING_BOX > platform->getPosition().y)
        && (gameLoop.doodler->getPosition().y + DOODLER_BOTTOM_BOUNDING_BOX < platform->getPosition().y + platform->getTextureSize().y)
        && (gameLoop.doodler->get_dy() > 0))
        return 1;
    return 0;
}

void GameEngine::checkEnemyCollision(const std::shared_ptr<Enemy>& enemy)
{
    if (doesEnemyIntersect(enemy)) {
        // Enemy collision causes game over
        gameLoop.doodler->setPosition({gameLoop.doodler->getPosition().x, WINDOW_HEIGHT + 100});
        SoundManager::getInstance()->playSound("enemy");
    }
}

bool GameEngine::doesEnemyIntersect(const std::shared_ptr<Enemy>& enemy) const
{
    if ((gameLoop.doodler->getPosition().x + DOODLER_RIGHT_BOUNDING_BOX > enemy->getPosition().x)
        && (gameLoop.doodler->getPosition().x + DOODLER_LEFT_BOUNDING_BOX < enemy->getPosition().x + enemy->getTextureSize().x)
        && (gameLoop.doodler->getPosition().y + DOODLER_BOTTOM_BOUNDING_BOX > enemy->getPosition().y)
        && (gameLoop.doodler->getPosition().y < enemy->getPosition().y + enemy->getTextureSize().y))
        return 1;
    return 0;
}

bool GameEngine::shouldShowEnemies() const
{
    // Enemies appear in waves starting at score 500, then 600, 700, 800, etc.
    // This means enemies show when score >= 500 (floor(score / 100) >= 5)
    float currentScore = gameLoop.totalScore.getScore();
    return (static_cast<int>(currentScore / 100) >= 5);
}

void GameEngine::manageEnemySound(const std::shared_ptr<Enemy>& enemy, SoundManager* soundMgr)
{
    // Check if enemy is on-screen (visible in SFML frame)
    bool isEnemyOnScreen = (enemy->getPosition().y >= 0 && enemy->getPosition().y <= WINDOW_HEIGHT);
    
    if (isEnemyOnScreen && !isEnemySoundPlaying) {
        // Enemy just appeared on screen - start playing sound
        soundMgr->playSound("enemy");
        isEnemySoundPlaying = true;
    } 
    else if (!isEnemyOnScreen && isEnemySoundPlaying) {
        // Enemy left the screen - stop playing sound
        soundMgr->stopSound("enemy");
        isEnemySoundPlaying = false;
    }
}

void GameEngine::run() 
{
    // Initialize SoundManager and load all sounds
    soundManager = SoundManager::getInstance();
    
    // Load all game sounds
    soundManager->loadSound("gameIntro", SOUND_GAME_INTRO);
    soundManager->loadSound("gameStart", SOUND_GAME_START);
    soundManager->loadBackgroundMusic(SOUND_BACKGROUND);
    soundManager->loadSound("jump", SOUND_JUMP);
    soundManager->loadSound("fall", SOUND_FALL);
    soundManager->loadSound("enemy", SOUND_ENEMY);
    
    // Play intro sound
    soundManager->playSound("gameIntro");
    
    // Display start menu
    StartMenu menu(gameLoop.getWindow());
    bool menuResult = menu.display(soundManager);
    
    if (!menuResult) {
        return;  // User closed the window
    }

    Logger::getInstance() << "Starting Doodle Jump..." << '\n';
    
    // Play background music when game starts
    soundManager->playBackgroundMusic();

    bool gameIsOver = false;
    while (gameLoop.getWindow().isOpen() && !gameIsOver) 
    {
        gameLoop.pollEvents();
        gameLoop.update();
        gameLoop.updateScore();
        checkCollision();
        gameLoop.redrawFrame();

        gameIsOver = checkGameOver(gameLoop.doodler);
    }
    if (gameIsOver) {
        soundManager->stopBackgroundMusic();
        soundManager->playSound("fall");
        displayGameOverWindow();
    }
}

void GameEngine::displayGameOverWindow() {
    Logger::getInstance() << "Doodle Jump Over!" << '\n';

    gameLoop.getWindow().clear(sf::Color::Black);

    sf::Font font;
    font.loadFromFile("res/font/arial.ttf");
    sf::Text gameoverText;
    gameoverText.setFont(font);
    gameoverText.setString("Game Over!");
    gameoverText.setCharacterSize(60);
    gameoverText.setFillColor(sf::Color::White);
    gameoverText.setPosition(40, 200);

    gameLoop.getWindow().draw(gameoverText);

    // Display final score

    sf::Text finalScoreText;
    finalScoreText.setFont(font);   
    finalScoreText.setCharacterSize(40);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setString( "Score: " + std::to_string( static_cast<int>( gameLoop.totalScore.getScore() ) ) );
    // Center the final score text
    finalScoreText.setPosition(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f); //Window width divided by 2, same with height.
    finalScoreText.setOrigin(finalScoreText.getLocalBounds().width/2.0f, finalScoreText.getLocalBounds().height/2.0f);

    gameLoop.getWindow().draw(finalScoreText);
    
    gameLoop.getWindow().display();

    sf::Event event;
    while (gameLoop.getWindow().isOpen()) {
        while (gameLoop.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameLoop.getWindow().close();
            }
        }
    }
}