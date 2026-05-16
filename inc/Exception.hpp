/*
 * ====================================================================
 * FILE: Exception.hpp
 * MODULE: Data Systems & UI
 * AUTHOR: Khawaja Talha Hassan
 * 
 * DESCRIPTION:
 * Custom exception hierarchy for the Doodle Jump game. Provides base
 * Exception class inheriting from std::exception with custom error messages.
 * Derived exception classes handle specific error conditions:
 * - UndefinedPlatformException: Invalid platform type selection
 * - IncorrectFilePathException: Missing or invalid resource file paths
 * Enables granular error handling with context-specific information.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Exception Handling: Custom exception class inheriting from std::exception
 * - Inheritance: Base Exception class for exception hierarchy
 * - Virtual Functions: virtual what() override for error message retrieval
 * - Encapsulation: Protected errorMessage member accessible to derived classes
 * - Polymorphism: Multiple exception types for specific error conditions
 * - noexcept Specification: Prevents exception propagation in destructors
 * - Derived Exception Classes: Specialized exceptions for domain-specific errors
 * ====================================================================
 */

#pragma once

#include <string>
#include <exception>

class Exception : public std::exception
{
protected:
    std::string errorMessage;
public: 
    explicit Exception(const std::string& message) : errorMessage(message) {}

    // using noexcept because throw() is deprecated
    virtual ~Exception() noexcept {}

    virtual const char* what() const noexcept override 
    { 
        return errorMessage.c_str(); 
    }
};

class UndefinedPlatformException : public Exception
{
public:
    explicit UndefinedPlatformException() : Exception("Platform type undefined!") {}
};

class IncorrectFilePathException : public Exception
{
private:
    std::string filePath;
public:
    explicit IncorrectFilePathException(std::string filePath) : Exception("The following filepath is incorrect: "), 
                                                                filePath(filePath)
    {
        errorMessage = errorMessage + filePath + "!";
    }
};