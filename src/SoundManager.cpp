/*
 * ====================================================================
 * FILE: SoundManager.cpp
 * MODULE: Utilities & Support
 * AUTHOR: Wasiq Mansoor
 * 
 * DESCRIPTION:
 * Implementation of the SoundManager Singleton class. Manages all audio
 * playback for the game including sound effects and background music.
 * Provides centralized sound management to avoid duplicate instances.
 * 
 * KEY CONCEPTS IMPLEMENTED:
 * - Singleton Implementation: Static instance, getInstance() method
 * - Resource Loading: Dynamic sound buffer loading from files
 * - Error Handling: Verifies file existence before loading
 * - Encapsulation: All sound management hidden behind public interface
 * ====================================================================
 */

#include "SoundManager.hpp"
#include "Logger.hpp"
#include <filesystem>

// Initialize static instance pointer
SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
    Logger::getInstance() << "SoundManager initialized.\n";
}

SoundManager::~SoundManager()
{
    stopBackgroundMusic();
    Logger::getInstance() << "SoundManager destroyed.\n";
}

SoundManager* SoundManager::getInstance()
{
    if (instance == nullptr) {
        instance = new SoundManager();
    }
    return instance;
}

bool SoundManager::loadSound(const std::string& soundName, const std::string& filePath)
{
    // Check if sound already loaded
    if (soundBuffers.find(soundName) != soundBuffers.end()) {
        Logger::getInstance() << "Sound '" << soundName << "' already loaded.\n";
        return true;
    }
    
    // Check if file exists
    if (!std::filesystem::exists(filePath)) {
        Logger::getInstance() << "Sound file not found: " << filePath << "\n";
        return false;
    }
    
    // Create temporary sound buffer
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        Logger::getInstance() << "Failed to load sound: " << filePath << "\n";
        return false;
    }
    
    // Store buffer and create associated sound
    soundBuffers[soundName] = buffer;
    sounds[soundName].setBuffer(soundBuffers[soundName]);
    
    Logger::getInstance() << "Sound loaded successfully: " << soundName << "\n";
    return true;
}

bool SoundManager::loadBackgroundMusic(const std::string& filePath)
{
    if (!std::filesystem::exists(filePath)) {
        Logger::getInstance() << "Background music file not found: " << filePath << "\n";
        return false;
    }
    
    if (!backgroundMusic.openFromFile(filePath)) {
        Logger::getInstance() << "Failed to load background music: " << filePath << "\n";
        return false;
    }
    
    backgroundMusic.setLoop(true);
    Logger::getInstance() << "Background music loaded: " << filePath << "\n";
    return true;
}

void SoundManager::playSound(const std::string& soundName)
{
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        it->second.play();
        Logger::getInstance() << "Playing sound: " << soundName << "\n";
    } else {
        Logger::getInstance() << "Sound not found: " << soundName << "\n";
    }
}

void SoundManager::stopSound(const std::string& soundName)
{
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        it->second.stop();
        Logger::getInstance() << "Stopped sound: " << soundName << "\n";
    }
}

void SoundManager::playBackgroundMusic()
{
    if (backgroundMusic.getStatus() != sf::Music::Playing) {
        backgroundMusic.play();
        Logger::getInstance() << "Playing background music.\n";
    }
}

void SoundManager::stopBackgroundMusic()
{
    if (backgroundMusic.getStatus() == sf::Music::Playing) {
        backgroundMusic.stop();
        Logger::getInstance() << "Stopped background music.\n";
    }
}

void SoundManager::setSoundVolume(const std::string& soundName, float volume)
{
    // Clamp volume between 0 and 100
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 100.0f) volume = 100.0f;
    
    auto it = sounds.find(soundName);
    if (it != sounds.end()) {
        it->second.setVolume(volume);
    }
}

void SoundManager::setBackgroundMusicVolume(float volume)
{
    // Clamp volume between 0 and 100
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 100.0f) volume = 100.0f;
    
    backgroundMusic.setVolume(volume);
}
