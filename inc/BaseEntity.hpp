/*
 * ====================================================================
 * FILE: BaseEntity.hpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Abstract base class for all game entities (Doodler and Platforms).
 * Inherits from sf::Drawable to support SFML rendering. Defines the
 * interface for position management and texture handling through pure
 * virtual functions, establishing the contract for all derived classes.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Abstract Base Class: Pure virtual functions (getPosition, setPosition, etc.)
 * - Inheritance: Inherits from sf::Drawable for polymorphic drawing
 * - Virtual Functions: Pure virtual methods force implementation in derived classes
 * - Encapsulation: Protected members (position, texture, sprite)
 * - Polymorphism: Enables runtime binding for draw() and accessor methods
 * ====================================================================
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"

// inherit Drawable for draw()
// Note: I could've also inherited sf::Transformable for getposition(), but I eventually wrote my own method.
class BaseEntity : public sf::Drawable
{
protected: 
    sf::Vector2f position;
    
    sf::Texture texture;
    
    sf::Sprite sprite;
public:
    virtual ~BaseEntity() = 0;

    virtual sf::Vector2f getPosition() const = 0;

    virtual void setPosition(sf::Vector2f ) = 0;

    virtual sf::Vector2u getTextureSize() = 0;
};

