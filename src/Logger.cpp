/*
 * ====================================================================
 * FILE: Logger.cpp
 * MODULE: Engine Architecture & Core
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Implementation of the Logger singleton pattern. Provides centralized
 * logging functionality across the application with thread-safe instance
 * retrieval and operator-based output streaming.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Singleton Pattern: Static instance management with getInstance()
 * - Private Constructor: Prevents external instantiation
 * - Static Methods: getInstance() returns static logger instance
 * ====================================================================
 */

#include "Logger.hpp"

Logger::Logger() {}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}