/*
 * ====================================================================
 * FILE: FastPlatform.cpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Concrete implementation of fast platform type providing maximum jump
 * height. Enables high-altitude gameplay sections with increased difficulty
 * and rewards for skilled players.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Function Overriding: Implements getDistance() with maximum height
 * - Polymorphism: Returns platform-specific jump distance value
 * - Inheritance Chain: Part of multi-level inheritance hierarchy
 * ====================================================================
 */

#include "FastPlatform.hpp"

FastPlatform::FastPlatform() : Platform()   // position is set is the base class Platform
{
    texture.loadFromFile(FAST_PLATFORM_FILEPATH);
    sprite.setTexture(texture);
}

FastPlatform::~FastPlatform() {}

unsigned FastPlatform::getDistance()
{
    return FAST_PLATFORM_DISTANCE;
}