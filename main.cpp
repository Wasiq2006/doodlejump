/*
 * ====================================================================
 * FILE: main.cpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Entry point of the Doodle Jump game application. Initializes the
 * GameEngine and starts the main game loop. Demonstrates the use of
 * object instantiation and control flow management.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Object Instantiation: GameEngine object creation
 * - Main Control Flow: Entry point delegation to GameEngine
 * ====================================================================
 */

#include <iostream>

#include "Logger.hpp"
#include "GameEngine.hpp"

int main()
{
    GameEngine gameEngine;

    gameEngine.run();

    return EXIT_SUCCESS;
}