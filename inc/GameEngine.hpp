/*
 * ====================================================================
 * FILE: GameEngine.hpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Core engine class responsible for game state management, collision
 * detection, and overall game flow control. Acts as orchestrator between
 * GameLoop and game logic, implementing lambda-based collision checking
 * and game-over detection using RTTI (dynamic_pointer_cast).
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Lambda Expressions: Collision checking and game-over detection lambdas
 * - RTTI (Dynamic Casting): Runtime type checking with dynamic_pointer_cast
 * - Composition: Contains GameLoop object and collaborates with Doodler/Platform
 * - Encapsulation: Private collision detection methods and lambda definitions
 * - Static Binding: Game loop coordination and frame-by-frame updates
 * ====================================================================
 */

#pragma once

#include <memory>
#include <random>

#include "GameLoop.hpp"
#include "Logger.hpp"
#include "StartMenu.hpp"
#include "SoundManager.hpp"

// Game engine responsible for collision detection & running and stopping the game
class GameEngine
{
private:
    GameLoop gameLoop;
    
    SoundManager* soundManager = nullptr;  // Pointer to SoundManager for sound control
    bool isEnemySoundPlaying = false;  // Track if enemy sound is currently playing

    const lambda<void> processCollisionForEach = [&](const std::shared_ptr<Platform>& platform) -> void {
        processCollision(platform);
    };

    const lambda<bool, Doodler> checkGameOver = [&](const std::shared_ptr<Doodler>& doodler) {
        return (doodler != nullptr && doodler->getPosition().y > WINDOW_HEIGHT);
    };

    void processCollision(const std::shared_ptr<Platform>&);

    bool doesIntersect(const std::shared_ptr<Platform>&) const;
    
    // Enemy collision detection
    void checkEnemyCollision(const std::shared_ptr<Enemy>&);
    
    bool doesEnemyIntersect(const std::shared_ptr<Enemy>&) const;
    
    // Check if enemies should be active at current score (500, 600, 700, etc.)
    bool shouldShowEnemies() const;
    
    // Manage enemy sound based on whether enemy is on screen
    void manageEnemySound(const std::shared_ptr<Enemy>& enemy, SoundManager* soundMgr);
public:
    ~GameEngine();

    void checkCollision();

    void run();

    void displayGameOverWindow();
};