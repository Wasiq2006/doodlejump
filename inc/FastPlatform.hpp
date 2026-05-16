/*
 * ====================================================================
 * FILE: FastPlatform.hpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Concrete platform type providing maximum jump height boost. Derived from
 * Platform, implements getDistance() to return FAST_PLATFORM_DISTANCE,
 * enabling players to reach higher altitudes. Creates gameplay variety
 * through different platform mechanics and visual feedback.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Multi-level Inheritance: Inherits from Platform (Platform -> BaseEntity)
 * - Function Overriding: Implements getDistance() with highest jump value
 * - Polymorphism: Different jump distances enable varied game mechanics
 * - Concrete Implementation: Provides concrete platform behavior
 * ====================================================================
 */

#pragma once

#include "Platform.hpp"

class FastPlatform : public Platform
{
public:
    FastPlatform();

    ~FastPlatform();

    unsigned getDistance() override;
};