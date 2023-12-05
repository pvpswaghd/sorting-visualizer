#pragma once
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include <map>
#include "Variables.h"

class Sound
{
public:
    static void initialize(int size);
    static void playSound(int height);
    static void stopSound();

private:
    static inline std::map<int, sf::SoundBuffer> soundMap;
    static inline sf::Sound sound;
    static std::vector<sf::Int16> generateSineWave(float frequency, float seconds);
};