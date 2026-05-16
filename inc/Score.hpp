/*
 * ====================================================================
 * FILE: Score.hpp
 * MODULE: Data Systems & UI
 * AUTHOR: Khawaja Talha Hassan
 * 
 * DESCRIPTION:
 * Template-based score management class supporting generic numeric types.
 * Implements operator overloading for score addition and assignment.
 * Enables type-safe score accumulation and persistence throughout game sessions
 * with compile-time type safety via templates.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Class Templates: Generic Score class accepting any numeric type T
 * - Template Methods: Templated getScore(), operator+, operator= implementations
 * - Operator Overloading: + for score addition, = for assignment
 * - Copy Constructor: Copy constructor for deep copying score objects
 * - Copy Assignment: Operator= for safe copy assignment semantics
 * - Data Type Abstraction: Works with any numeric type (int, float, double)
 * ====================================================================
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"

// Score Counter class
template<typename T>
class Score     
{
private:
    T score;
public:
    Score(T score = 0);

    ~Score();

    Score(const Score<T>& ob);

    T getScore() const;

    Score<T>& operator=(const Score<T>& );

    // Overload + operator. When incrementing the score - increment the total score with 
    // another ScoreCounter instance having the current obtained score as value.
    Score<T> operator + (Score<T> const&);
};
