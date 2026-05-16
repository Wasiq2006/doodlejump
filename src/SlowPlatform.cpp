/*
 * ====================================================================
 * FILE: SlowPlatform.cpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Concrete implementation of slow/fragile platform type. Provides reduced
 * jump distance and collision tracking. Represents platforms that disappear
 * after first collision, adding strategic gameplay elements.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Function Overriding: Implements getDistance() with reduced height
 * - State Management: Manages hasCollision flag for platform destruction
 * - Encapsulation: Private hasCollision with getter/setter accessors
 * - Polymorphism: Different behavior based on platform type
 * ====================================================================
 */

#include "SlowPlatform.hpp"

SlowPlatform::SlowPlatform() : Platform()   // position is set is the base class Platform
{
    texture.loadFromFile(SLOW_PLATFORM_FILEPATH);
    sprite.setTexture(texture);

    hasCollision = false;
}

SlowPlatform::~SlowPlatform() {}

unsigned SlowPlatform::getDistance()
{
    return SLOW_PLATFORM_DISTANCE;
}

bool SlowPlatform::getHasCollision() const 
{
    return hasCollision;
}

void SlowPlatform::setHasCollision(bool value) 
{
    hasCollision = value;
}