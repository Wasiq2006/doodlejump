/*
 * ====================================================================
 * FILE: StartMenu.hpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Manages the start menu screen with attractive UI featuring gradient
 * backgrounds, decorative elements, and animated blinking effects.
 * Displays game title, instructions, and controls with professional
 * styling. Waits for spacebar input to transition to the main game.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Encapsulation: Menu state and window reference management
 * - Composition: Contains game window reference for rendering
 * - Event Handling: Spacebar input detection for menu progression
 * - SFML Integration: Advanced text rendering with outlines, shapes, colors
 * - Animation: Blinking effect for user attention
 * - Responsive Design: Centered layout compatible with game resolution
 * ====================================================================
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Logger.hpp"

class SoundManager;  // Forward declaration

class StartMenu
{
private:
    sf::RenderWindow& window;

public:
    StartMenu(sf::RenderWindow& gameWindow);

    ~StartMenu();

    // Display menu and wait for spacebar input
    // Returns true when spacebar is pressed
    bool display(SoundManager* soundManager = nullptr);
};
