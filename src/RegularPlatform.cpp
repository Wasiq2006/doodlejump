/*
 * ====================================================================
 * FILE: RegularPlatform.cpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Concrete implementation of regular platform type. Provides specific
 * jump distance (REGULAR_PLATFORM_DISTANCE) and initialization logic
 * for the standard platform entity in the game hierarchy.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Function Overriding: Implements pure virtual getDistance() method
 * - Polymorphism: Returns platform-specific jump distance value
 * - Constructor/Destructor: Manages platform initialization and cleanup
 * ====================================================================
 */

#include "RegularPlatform.hpp"

RegularPlatform::RegularPlatform() : Platform()     // position is set is the base class Platform
{
    texture.loadFromFile(PLATFORM_FILEPATH);
    sprite.setTexture(texture);
}

RegularPlatform::~RegularPlatform() {}

unsigned RegularPlatform::getDistance()
{
    return REGULAR_PLATFORM_DISTANCE;
}