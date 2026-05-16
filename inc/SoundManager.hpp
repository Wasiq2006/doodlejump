/*
 * ====================================================================
 * FILE: SoundManager.hpp
 * MODULE: Utilities & Support
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Singleton pattern for managing all game sounds. Provides centralized
 * control for loading and playing audio files (music and sound effects).
 * Ensures only one instance exists throughout the game lifetime.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Singleton Pattern: Private constructor, static getInstance()
 * - Encapsulation: Private member variables and methods
 * - Resource Management: SFML SoundBuffer and Sound objects
 * - State Management: Track currently playing sounds
 * ====================================================================
 */

#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

class SoundManager
{
private:
    // Singleton: Private static instance
    static SoundManager* instance;
    
    // Private constructor - prevent instantiation
    SoundManager();
    
    // Sound buffers storage
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    
    // Sound objects for playing
    std::map<std::string, sf::Sound> sounds;
    
    // Background music
    sf::Music backgroundMusic;

public:
    // Singleton access method
    static SoundManager* getInstance();
    
    // Delete copy constructor and assignment operator
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
    
    // Destructor
    ~SoundManager();
    
    // Load sound from file
    // Returns true if successful, false if file not found or already loaded
    bool loadSound(const std::string& soundName, const std::string& filePath);
    
    // Load and play background music (loops)
    bool loadBackgroundMusic(const std::string& filePath);
    
    // Play a sound effect
    void playSound(const std::string& soundName);
    
    // Stop a sound
    void stopSound(const std::string& soundName);
    
    // Play background music
    void playBackgroundMusic();
    
    // Stop background music
    void stopBackgroundMusic();
    
    // Set volume for a sound (0-100)
    void setSoundVolume(const std::string& soundName, float volume);
    
    // Set background music volume (0-100)
    void setBackgroundMusicVolume(float volume);
};
