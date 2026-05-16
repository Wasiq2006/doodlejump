/*
 * ====================================================================
 * FILE: Logger.hpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Implements the Logger class using the Singleton Design Pattern.
 * Provides centralized error and debug message output to stderr using
 * operator overloading for stream manipulation.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Singleton Pattern: Private constructor, static getInstance() method
 * - Operator Overloading: Overloaded << operator for flexible logging
 * - Template Implementation: Templated operator<< for generic type logging
 * - Design Pattern: Ensures single instance across application lifetime
 * ====================================================================
 */

#pragma once

#include <iostream>

class Logger
{
    Logger();

    Logger(const Logger& ) = delete;
    
    Logger& operator=(const Logger& ) = delete;
public:
    static Logger& getInstance();

    // `<<` operator implemented inline
    template <class T>
    Logger& operator<<(const T& item)
    {
        std::cerr << item;
        return *this;
    }
};
