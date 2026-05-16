/*
 * ====================================================================
 * FILE: Keyboard.cpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Implementation of keyboard input handling with operator overloading.
 * Manages key state tracking for left/right movement controls and
 * processes SFML keyboard events into internal state map.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Operator Overloading: += and -= operators for key press/release
 * - STL Containers: std::map for key state management
 * - Event Processing: Converts SFML events to internal key state
 * - Encapsulation: Controls access to internal keysMap via getters
 * ====================================================================
 */

#include "Keyboard.hpp"

Keyboard::Keyboard()
{
    keysMap[sf::Keyboard::Left] = false;
    keysMap[sf::Keyboard::Right] = false;
}

std::map<sf::Keyboard::Key, bool> Keyboard::getKeysMap() const
{
    return keysMap;
}

void Keyboard::inputHandler(const sf::Event& event)
{
    switch (event.type) {
        case sf::Event::KeyPressed:
            (*this) += event.key.code;
            break;
        case sf::Event::KeyReleased:
            (*this) -= event.key.code;
            break;
        default:
            break;
    }
}

Keyboard& Keyboard::operator+=(const sf::Keyboard::Key& key)    // KeyPressed
{
    if (key == sf::Keyboard::Right) {
        keysMap[sf::Keyboard::Right] = true;
    } else {
        keysMap[sf::Keyboard::Left] = true;
    }
    return (*this);
}

Keyboard& Keyboard::operator-=(const sf::Keyboard::Key& key)    // KeyReleased
{
    if (key == sf::Keyboard::Right) {
        keysMap[sf::Keyboard::Right] = false;
    } else {
        keysMap[sf::Keyboard::Left] = false;
    }
    return (*this);
}