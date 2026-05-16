/*
 * ====================================================================
 * FILE: BaseEntity.cpp
 * MODULE: Entity & Inheritance Management
 * AUTHOR: Sumiad Ahmed
 * 
 * DESCRIPTION:
 * Implementation of the abstract BaseEntity class. Provides the pure
 * virtual destructor implementation and serves as the root of the
 * inheritance hierarchy for all drawable game objects.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Abstract Base Class: Pure virtual destructor must be defined
 * - Inheritance Foundation: Base class for Doodler and Platform
 * - Virtual Destructor: Enables proper cleanup of derived objects
 * ====================================================================
 */

#include "BaseEntity.hpp"

BaseEntity::~BaseEntity() {}