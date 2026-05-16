/*
 * ====================================================================
 * FILE: Doodler.hpp
 * MODULE: Physics & Collision Logic
 * AUTHOR: Sudias Khan
 * 
 * DESCRIPTION:
 * Represents the player-controlled character (Doodle) in the game.
 * Inherits from BaseEntity and implements physics-based vertical movement
 * with user-controlled horizontal input. Manages position, velocity (dy),
 * keyboard input handling, and collision physics through encapsulated methods.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Inheritance: Inherits from BaseEntity with override of virtual methods
 * - Encapsulation: Private dy (velocity) with getter/setter methods
 * - Copy Constructor & Assignment Operator: User-defined copy semantics
 * - Operator Overloading: Overloaded = for assignment and copy constructor
 * - Physics Implementation: Velocity and position management
 * - Virtual Function Overriding: Overrides draw(), getPosition(), setPosition()
 * - Exception Handling: File loading with custom exception handling
 * - Composition: Contains Keyboard object for input management
 * ====================================================================
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>

#include "DEFINITIONS.hpp"
#include "BaseEntity.hpp"
#include "Keyboard.hpp"
#include "Exception.hpp"
#include "Logger.hpp"

class Doodler : public BaseEntity
{
private:
    float dy;   // delta y
    
    // Overriding sf::Drawable::draw
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void setLeftRightPosition(const float, const float);
    
    Keyboard keyboardInput;     
public:
    Doodler();

    ~Doodler();

    Doodler(const Doodler&);

    Doodler& operator=(const Doodler&);

    void updatePosition(const float);

    sf::Vector2f getPosition() const override; 

    void setPosition(sf::Vector2f ) override;

    sf::Vector2u getTextureSize() override;

    void setUpDownPosition();

    float get_dy() const;

    void set_dy(float);

    void handleKeyboardInput(const sf::Event&);
};