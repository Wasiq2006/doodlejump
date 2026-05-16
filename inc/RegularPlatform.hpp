/*
 * ====================================================================
 * FILE: RegularPlatform.hpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Concrete platform type derived from Platform. Represents the standard
 * jump platform with regular height boost. Implements the pure virtual
 * getDistance() method from Platform to define the jump distance for
 * regular platforms (REGULAR_PLATFORM_DISTANCE constant).
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Multi-level Inheritance: Inherits from Platform (which inherits BaseEntity)
 * - Function Overriding: Overrides pure virtual getDistance() from Platform
 * - Polymorphism: Enables runtime selection of jump distance based on platform type
 * - Concrete Implementation: First concrete class in Platform hierarchy
 * ====================================================================
 */

#pragma once

#include "Platform.hpp"

class RegularPlatform : public Platform
{
public:
    RegularPlatform();

    ~RegularPlatform();

    unsigned getDistance() override;
};