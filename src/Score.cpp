/*
 * ====================================================================
 * FILE: Score.cpp
 * MODULE: Data Systems & UI
 * AUTHOR: Khawaja Talha Hassan
 * 
 * DESCRIPTION:
 * Template implementation for the Score class providing generic score
 * management with operator overloading. Supports score addition, assignment,
 * and retrieval with compile-time type safety.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Class Templates: Generic implementation for any numeric type
 * - Template Methods: Template operator overloads for + and =
 * - Copy Constructor: Deep copy semantics for score objects
 * - Assignment Operator: Safe assignment with value copying
 * - Destructor: Resets score on object destruction
 * ====================================================================
 */

#include "Score.hpp"

template<typename T>
Score<T>::Score(T score) : score(score) {}

template<typename T>
Score<T>::~Score() 
{
    score = 0;
}

template<typename T>
Score<T>::Score(const Score<T>& ob)     // copy constructor
{
    score = ob.score;
}

template<typename T>
T Score<T>::getScore() const
{
    return this->score;
}

template<typename T>
Score<T>& Score<T>::operator=(const Score<T>& other) 
{
    if (this == &other) {
        return (*this);
    }
    score = other.score;
    return (*this);
}

template<typename T>
Score<T> Score<T>::operator+ (Score<T> const& ob) 
{ 
    Score newScore;
    newScore.score = this->score + ob.score;
    return newScore;
} 

template class Score<int>;  
// This will ensure that, when the compiler is compiling Score.cpp 
// that it will explicitly compile all the code for the Score<int>

template class Score<float>;  
