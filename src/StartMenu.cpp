/*
 * ====================================================================
 * FILE: StartMenu.cpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Implementation of the enhanced StartMenu class with attractive UI design.
 * Renders gradient backgrounds, decorative circles, and styled text with
 * outlines. Implements blinking animation for the start instruction.
 * Handles spacebar input for smooth menu-to-game transition.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Event Handling: Polls spacebar, close events, and timing for animations
 * - SFML Rendering: Multiple shapes, text with outlines, gradient effects
 * - Animation Loop: Blinking counter for text effects at 60 FPS
 * - Color Gradients: Multiple rectangles for background gradient appearance
 * - Responsive Layout: Centered elements using getLocalBounds() and origin
 * - Exception Handling: Font file loading with custom exception handling
 * ====================================================================
 */

#include <filesystem>
#include "StartMenu.hpp"
#include "SoundManager.hpp"
#include "Exception.hpp"

StartMenu::StartMenu(sf::RenderWindow& gameWindow) : window(gameWindow)
{
}

StartMenu::~StartMenu() {}

bool StartMenu::display(SoundManager* soundManager)
{
    Logger::getInstance() << "Displaying Start Menu..." << '\n';

    sf::Font font;
    try {
        if (!std::filesystem::exists(FONT_FILEPATH))
            throw IncorrectFilePathException(FONT_FILEPATH);
        font.loadFromFile(FONT_FILEPATH);
    }
    catch(IncorrectFilePathException& e) {
        Logger::getInstance() << "Exception: " << e.what() << '\n';
        return false;
    }

    // Background rectangle with gradient effect (using multiple rectangles)
    sf::RectangleShape topGradient(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 3));
    topGradient.setPosition(0, 0);
    topGradient.setFillColor(sf::Color(100, 150, 255));  // Light blue

    sf::RectangleShape bottomGradient(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT * 2 / 3));
    bottomGradient.setPosition(0, WINDOW_HEIGHT / 3);
    bottomGradient.setFillColor(sf::Color(135, 206, 250));  // Sky blue

    // Decorative circles
    sf::CircleShape circle1(60);
    circle1.setFillColor(sf::Color(255, 200, 100, 150));
    circle1.setPosition(-40, -30);

    sf::CircleShape circle2(80);
    circle2.setFillColor(sf::Color(100, 200, 255, 120));
    circle2.setPosition(WINDOW_WIDTH - 50, WINDOW_HEIGHT - 100);

    // Main title text
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("DOODLE JUMP");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color(255, 255, 255));
    titleText.setOutlineThickness(2);
    titleText.setOutlineColor(sf::Color::Blue);
    titleText.setPosition(WINDOW_WIDTH / 2.0f, 55);
    titleText.setOrigin(titleText.getLocalBounds().width / 2.0f, titleText.getLocalBounds().height / 2.0f);

    // Subtitle text
    sf::Text subtitleText;
    subtitleText.setFont(font);
    subtitleText.setString("Jump to the Top!");
    subtitleText.setCharacterSize(24);
    subtitleText.setFillColor(sf::Color(255, 255, 100));
    subtitleText.setPosition(WINDOW_WIDTH / 2.0f, 110);
    subtitleText.setOrigin(subtitleText.getLocalBounds().width / 2.0f, subtitleText.getLocalBounds().height / 2.0f);

    // Main instruction text with styling
    sf::Text instructionsText;
    instructionsText.setFont(font);
    instructionsText.setString("Press SPACE to Start");
    instructionsText.setCharacterSize(32);
    instructionsText.setFillColor(sf::Color(255, 255, 255));
    instructionsText.setOutlineThickness(1);
    instructionsText.setOutlineColor(sf::Color::Black);
    instructionsText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - 20);
    instructionsText.setOrigin(instructionsText.getLocalBounds().width / 2.0f, instructionsText.getLocalBounds().height / 2.0f);

    // Game controls text
    sf::Text controlsText;
    controlsText.setFont(font);
    controlsText.setString("← LEFT  |  RIGHT →");
    controlsText.setCharacterSize(20);
    controlsText.setFillColor(sf::Color(0, 0, 0));
    controlsText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 40);
    controlsText.setOrigin(controlsText.getLocalBounds().width / 2.0f, controlsText.getLocalBounds().height / 2.0f);

    // Controls description
    sf::Text controlsDescText;
    controlsDescText.setFont(font);
    controlsDescText.setString("Use Arrow Keys to Move");
    controlsDescText.setCharacterSize(16);
    controlsDescText.setFillColor(sf::Color(50, 50, 50));
    controlsDescText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 70);
    controlsDescText.setOrigin(controlsDescText.getLocalBounds().width / 2.0f, controlsDescText.getLocalBounds().height / 2.0f);

    // Additional info text
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setString("Collect Points • Avoid Enemies • Reach the Sky!");
    infoText.setCharacterSize(14);
    infoText.setFillColor(sf::Color(100, 100, 100));
    infoText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 50);
    infoText.setOrigin(infoText.getLocalBounds().width / 2.0f, infoText.getLocalBounds().height / 2.0f);

    // Version/Footer text
    sf::Text footerText;
    footerText.setFont(font);
    footerText.setString("Doodle Jump - Version 1.0");
    footerText.setCharacterSize(12);
    footerText.setFillColor(sf::Color(150, 150, 150));
    footerText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 10);
    footerText.setOrigin(footerText.getLocalBounds().width / 2.0f, footerText.getLocalBounds().height / 2.0f);

    bool startPressed = false;
    float blinkCounter = 0.0f;
    bool blinkState = true;

    while (window.isOpen() && !startPressed)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    startPressed = true;
                    if (soundManager != nullptr) {
                        soundManager->playSound("gameStart");
                    }
                    Logger::getInstance() << "Game Starting..." << '\n';
                }
            }
        }

        // Blinking effect for spacebar text (every ~0.5 seconds)
        blinkCounter += 0.016f;  // Approximately 60 FPS
        if (blinkCounter > 0.5f) {
            blinkState = !blinkState;
            blinkCounter = 0.0f;
        }

        if (blinkState) {
            instructionsText.setFillColor(sf::Color(255, 255, 255));
        } else {
            instructionsText.setFillColor(sf::Color(200, 200, 200));
        }

        // Clear and draw menu
        window.clear(sf::Color(200, 220, 255));  // Light background

        // Draw decorative elements
        window.draw(topGradient);
        window.draw(bottomGradient);
        window.draw(circle1);
        window.draw(circle2);

        // Draw text elements
        window.draw(titleText);
        window.draw(subtitleText);
        window.draw(instructionsText);
        window.draw(controlsText);
        window.draw(controlsDescText);
        window.draw(infoText);
        window.draw(footerText);

        window.display();
    }

    return startPressed;
}
