/*
 * ====================================================================
 * FILE: Enemy.cpp
 * MODULE: Physics & Collision Logic
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Implementation of the Enemy class with horizontal movement and collision
 * detection. Enemies move across the screen and cause immediate game over
 * when colliding with the Doodler. Supports both left and right movement.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Inheritance: Overrides BaseEntity virtual methods
 * - Polymorphism: Runtime method dispatch for draw() and getPosition()
 * - Physics: Constant velocity horizontal movement with boundary wrapping
 * - Exception Handling: Try-catch for texture loading with custom exceptions
 * - Encapsulation: Private velocity and direction with controlled access
 * ====================================================================
 */

#include "Enemy.hpp"
#include "Exception.hpp"
#include "Logger.hpp"
#include <filesystem>

Enemy::Enemy(float x, float y, bool moveRight)
    : velocity(2.0f), movingRight(moveRight)
{
    position = sf::Vector2f(x, y);
    
    try {
        if (!std::filesystem::exists("res/img/Enemies.png"))
            throw IncorrectFilePathException("res/img/Enemies.png");
        texture.loadFromFile("res/img/Enemies.png");
    }
    catch(IncorrectFilePathException& e) {
        Logger::getInstance() << "Exception: " << e.what() << '\n';
    }
    
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

Enemy::~Enemy() {}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

sf::Vector2f Enemy::getPosition() const
{
    return position;
}

void Enemy::setPosition(sf::Vector2f newPosition)
{
    position = newPosition;
    sprite.setPosition(position);
}

sf::Vector2u Enemy::getTextureSize()
{
    return texture.getSize();
}

void Enemy::update()
{
    // Enemy stays at a fixed point (no horizontal movement)
    sprite.setPosition(position);
}

bool Enemy::isOutOfBounds() const
{
    return position.y > WINDOW_HEIGHT || position.y < -100;
}
