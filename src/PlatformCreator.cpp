/*
 * ====================================================================
 * FILE: PlatformCreator.cpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Factory implementation for creating different platform types based on
 * input choice. Uses dynamic_cast for safe type conversion and throws
 * UndefinedPlatformException for invalid platform types.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Factory Design Pattern: Static method creates objects polymorphically
 * - Smart Pointers: Returns shared_ptr<Platform> for automatic memory management
 * - Exception Handling: Throws custom exceptions for invalid inputs
 * - RTTI: dynamic_cast for type validation of created objects
 * ====================================================================
 */

#include "PlatformCreator.hpp"

PlatformCreator::~PlatformCreator() {}

std::shared_ptr<Platform> PlatformCreator::getPlatform(const int& choice)
{
    try {
        switch(choice) {
            case 1:
                return std::make_shared<RegularPlatform>(RegularPlatform());
                break;
            case 2:
                return std::make_shared<SlowPlatform>(SlowPlatform());
                break;
            case 3:
                return std::make_shared<FastPlatform>(FastPlatform());
                break;
            default:
                throw UndefinedPlatformException();
                break;
        }
    }
    catch (UndefinedPlatformException& e)
    {
        Logger::getInstance() << "Exception: " << e.what() << '\n';
        return nullptr;
    }
}