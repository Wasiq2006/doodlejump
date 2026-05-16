/*
 * ====================================================================
 * FILE: Enemy.hpp
 * MODULE: Physics & Collision Logic
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Defines the Enemy class representing obstacles that move horizontally
 * across the screen. Inherits from BaseEntity and implements collision
 * detection with the Doodler character. Enemies cause immediate game over
 * on contact with the player.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Inheritance: Inherits from BaseEntity with virtual method overrides
 * - Polymorphism: Virtual draw() and getPosition() implementations
 * - Encapsulation: Private velocity and direction management
 * - SFML Integration: Sprite-based rendering and texture management
 * - Physics: Horizontal movement with direction control
 * ====================================================================
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "BaseEntity.hpp"
#include "DEFINITIONS.hpp"

class Enemy : public BaseEntity
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float velocity;  // Speed of movement (pixels per frame)
    bool movingRight;  // Direction: true = moving right, false = moving left

public:
    Enemy(float x, float y, bool moveRight = true);
    ~Enemy();

    // Overridden virtual methods from BaseEntity
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    // Get enemy position
    sf::Vector2f getPosition() const override;
    
    // Set enemy position
    void setPosition(sf::Vector2f newPosition) override;
    
    // Get texture size for collision detection
    sf::Vector2u getTextureSize() override;
    
    // Update enemy position (horizontal movement)
    void update();
    
    // Get collision distance (0 for enemies - they cause instant game over)
    unsigned getDistance() const { return 0; }
    
    // Check if enemy is out of bounds
    bool isOutOfBounds() const;
    
    // Change movement direction
    void setDirection(bool moveRight) { movingRight = moveRight; }
    
    // Get current direction
    bool getDirection() const { return movingRight; }
};
