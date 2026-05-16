/*
 * ====================================================================
 * FILE: Keyboard.hpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Handles keyboard input management with operator overloading for key
 * press/release events. Maintains a map of key states for the Doodler's
 * left-right movement control. Encapsulates input handling logic.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Operator Overloading: += for key press, -= for key release
 * - Encapsulation: Private keysMap with controlled access via getKeysMap()
 * - STL Containers: std::map for key-to-state mapping
 * - Event Handling: inputHandler() for SFML event processing
 * ====================================================================
 */

#pragma once

#include <SFML/Graphics.hpp>

class Keyboard
{
private:
    std::map<sf::Keyboard::Key, bool> keysMap;
    
    Keyboard& operator+=(const sf::Keyboard::Key& key);  // KeyPressed
    
    Keyboard& operator-=(const sf::Keyboard::Key& key);  // KeyReleased
public:
    Keyboard();

    void inputHandler(const sf::Event& event);

    std::map<sf::Keyboard::Key, bool> getKeysMap() const;
};
