/*
 * ====================================================================
 * FILE: SlowPlatform.hpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Concrete platform type representing a fragile/slow platform that
 * disappears after collision. Extends Platform with hasCollision flag
 * to track if the platform has been used. Implements getDistance() to
 * provide reduced jump height (SLOW_PLATFORM_DISTANCE), creating varied
 * gameplay mechanics.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Multi-level Inheritance: Inherits from Platform hierarchy
 * - Function Overriding: Overrides getDistance() with platform-specific value
 * - State Management: Private hasCollision flag tracks platform usage
 * - Encapsulation: Private hasCollision with getter/setter methods
 * - Polymorphism: Different jump distances based on platform type
 * ====================================================================
 */

#pragma once

#include "Platform.hpp"

class SlowPlatform : public Platform
{
private:
    bool hasCollision;
public:
    SlowPlatform();

    ~SlowPlatform();

    unsigned getDistance() override;

    bool getHasCollision() const;

    void setHasCollision(bool);
};