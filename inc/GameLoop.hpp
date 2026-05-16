/*
 * ====================================================================
 * FILE: GameLoop.hpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Manages the rendering loop, window management, delta time calculations,
 * and game state updates. Maintains collections of game entities (Doodler,
 * Platforms) and handles frame rendering with SFML. Works closely with
 * GameEngine for collision and score management.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Composition: Contains Doodler, Platforms vector, Score template
 * - Smart Pointers: Uses shared_ptr for dynamic object management
 * - Friend Class: GameEngine accesses private members for game logic
 * - Template Usage: Score<float> for dynamic score calculation
 * - Encapsulation: Private window setup, state management
 * ====================================================================
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "DEFINITIONS.hpp"
#include "BaseEntity.hpp"
#include "Doodler.hpp"
#include "PlatformCreator.hpp"
#include "Score.hpp"
#include "Enemy.hpp"

class GameLoop 
{
private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Clock clock;

    float deltaTime = 0;

    void createWindow();

    std::shared_ptr<Doodler> doodler;    
    
    Platforms platforms;
    
    Enemies enemies;

    Score<float> totalScore;
public:
    GameLoop();

    ~GameLoop();
    
    void pollEvents();

    void update();

    void updateScore();

    void redrawFrame();

    sf::RenderWindow& getWindow();

    friend class GameEngine;
};