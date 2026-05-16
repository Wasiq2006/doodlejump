/*
 * ====================================================================
 * FILE: PlatformCreator.hpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Implements the Factory Design Pattern for creating different platform
 * types (Regular, Slow, Fast). The getPlatform() static factory method
 * abstracts platform instantiation logic, enabling polymorphic object
 * creation and returning shared_ptr to base Platform class.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Factory Design Pattern: Static getPlatform() factory method
 * - Polymorphism: Returns shared_ptr<Platform> (base class pointer)
 * - Smart Pointers: Uses shared_ptr for automatic memory management
 * - Exception Handling: Throws UndefinedPlatformException for invalid types
 * - Encapsulation: Platform instantiation logic hidden from client code
 * ====================================================================
 */

#pragma once

#include <memory>

#include "RegularPlatform.hpp"
#include "SlowPlatform.hpp"
#include "FastPlatform.hpp"
#include "Exception.hpp"
#include "Logger.hpp"

class PlatformCreator
{
public:
    ~PlatformCreator();

    static std::shared_ptr<Platform> getPlatform(const int& choice);    // Factory method
};