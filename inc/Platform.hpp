/*
 * ====================================================================
 * FILE: Platform.hpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Intermediate abstract class inheriting from BaseEntity, representing
 * the base platform type in the game. Implements position/texture
 * management with draw() marked as final. Defines pure virtual
 * getDistance() for platform-specific jump distances, enabling
 * multi-level inheritance hierarchy.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Multi-level Inheritance: Inherits from BaseEntity, parent to RegularPlatform, SlowPlatform, FastPlatform
 * - Virtual Functions: Pure virtual getDistance() for derived class implementation
 * - Final Methods: draw() marked final to prevent further override
 * - Operator Overloading: Copy constructor and assignment operator (= and copy ctor)
 * - Copy Control: User-defined copy constructor and assignment operator
 * ====================================================================
 */

#pragma once

#include <random>

#include "BaseEntity.hpp"
#include "DEFINITIONS.hpp"

class Platform : public BaseEntity
{
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
public:
    Platform();

    ~Platform();        // will also be virtual because virtual-ness propagates to derived classes

    Platform(const Platform&); 

    Platform& operator=(const Platform&);

    void updatePosition();

    sf::Vector2f getPosition() const override final; 

    void setPosition(sf::Vector2f ) override final;

    sf::Vector2u getTextureSize() override;

    // How far up the doodler will jump after collision with the plaform
    virtual unsigned getDistance() = 0;
};

