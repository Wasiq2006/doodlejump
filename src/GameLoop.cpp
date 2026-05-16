/*
 * ====================================================================
 * FILE: GameLoop.cpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Main game loop implementation managing window rendering, entity updates,
 * and frame-by-frame game state progression. Handles SFML window creation,
 * delta-time calculation for frame-rate independence, and redrawing of all
 * game entities and UI elements.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Game Loop Architecture: Update-render cycle pattern
 * - Delta Time: Frame-rate independent movement calculations
 * - Composition: Contains Doodler, Platforms, and Score objects
 * - Smart Pointers: shared_ptr for dynamic entity management
 * - Friend Class: Grants GameEngine access to private members
 * - Encapsulation: Private window setup and state management
 * ====================================================================
 */

#include "GameLoop.hpp"

void GameLoop::createWindow()
{   
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    window.setFramerateLimit(MAX_FPS);    
}

sf::RenderWindow& GameLoop::getWindow()
{
    return window;
}

GameLoop::GameLoop()
{
    if (!window.isOpen()) {
        createWindow();
    }        
                            
    backgroundTexture.loadFromFile(BACKGROUND_FILEPATH);
    backgroundSprite.setTexture(backgroundTexture);

    for (size_t i = 0; i < PLATFORM_COUNT; ++i) {
        // I wanted to have 2 times more regular_platfoms than slow/fast_platforms
        // x MOD 4 => 0 1 2 3 | MOD 3 => 0 1 2 0 | + 1 => 1 2 3 1 (Note: 1 = regular, 2 = slow & 3 = fast)
        int type = (i % 4) % 3 + 1;
        platforms.emplace_back(PlatformCreator::getPlatform(type));
    }

    // Initialize enemies at different horizontal positions
    for (size_t i = 0; i < ENEMY_COUNT; ++i) {
        float xPos = (WINDOW_WIDTH / (ENEMY_COUNT + 1)) * (i + 1);
        bool moveRight = (i % 2 == 0);  // Alternate directions
        enemies.emplace_back(std::make_shared<Enemy>(xPos, ENEMY_SPAWN_Y, moveRight));
    }

    doodler = std::make_shared<Doodler>(Doodler());
}

GameLoop::~GameLoop() {}

void GameLoop::pollEvents()
{
    deltaTime = clock.restart().asSeconds();
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else {
            doodler->handleKeyboardInput(event);
        }
    }    
}

void GameLoop::update()
{        
    doodler->updatePosition(deltaTime);

    const lambda<void> drawEach = [&](const std::shared_ptr<Platform>& platform) -> void {
        platform->updatePosition();
    };

    std::for_each(platforms.begin(), platforms.end(), drawEach);
    
    // Update all enemies only during active enemy waves (500+, 600+, 700+, etc.)
    if (totalScore.getScore() >= 500.0f && static_cast<int>(totalScore.getScore() / 100) >= 5) {
        std::for_each(enemies.begin(), enemies.end(),
            [&](const std::shared_ptr<Enemy>& enemy) -> void {
                enemy->update();
            });
    }
}

void GameLoop::updateScore()
{
    if (doodler->getPosition().y == DOODLER_HEIGHT && doodler->get_dy() < (-1.62)) {	// > (-1.62) means that the doodler is jumping on the same platform, therefore the score won't increase 
        Score<float> addScore(0.5);
        totalScore = totalScore + addScore;
    }
}

void GameLoop::redrawFrame()
{
    // Draw background
    window.draw(backgroundSprite);

    sf::Font font;
    font.loadFromFile(FONT_FILEPATH);
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Black);
    
    scoreText.setString( "Score: " + std::to_string(static_cast<int>(totalScore.getScore())));
    
    // Draw score
    window.draw(scoreText);

    // Draw doodler
    window.draw(*doodler);

    // Draw platforms
    std::for_each(platforms.begin(), platforms.end(), 
        [&](const std::shared_ptr<Platform>& item) -> void {
            if (std::shared_ptr<SlowPlatform> sp = std::dynamic_pointer_cast<SlowPlatform>(item)) {
                if (sp->getHasCollision() == false) {
                    window.draw(*item);
                }
                // is hasCollision = true, then that slow_platform should not be visible
                // (it 'disappears' after collision)
            }
            else {
                window.draw(*item);
            }
        });

    // Draw enemies only during active enemy waves (500+, 600+, 700+, etc.)
    if (totalScore.getScore() >= 500.0f && static_cast<int>(totalScore.getScore() / 100) >= 5) {
        std::for_each(enemies.begin(), enemies.end(),
            [&](const std::shared_ptr<Enemy>& enemy) -> void {
                window.draw(*enemy);
            });
    }

    window.display();
}
