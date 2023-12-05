#include "../include/Sound.h"


const int SAMPLE_RATE = 44100;
const float TWO_PI = 6.28318f;
const int AMPLITUDE = 30000;

std::vector<sf::Int16> Sound::generateSineWave(float frequency, float seconds)
{
    std::vector<sf::Int16> samples(seconds * SAMPLE_RATE);
    int sampleCount = 0;

    for (int i = 0; i < seconds * SAMPLE_RATE; i++)
    {
        float sampleFloat = AMPLITUDE * sin((TWO_PI * frequency) / SAMPLE_RATE * i);
        samples[sampleCount] = static_cast<sf::Int16>(sampleFloat);
        sampleCount++;
    }

    return samples;
}

void Sound::initialize(int size)
{
    for (int i = 0; i < size; ++i)
    {
        sf::SoundBuffer buffer;
        auto samples = generateSineWave(i * 150, Variables::delayMs-10); // 10 Hz per height unit, for 0.1 seconds
        buffer.loadFromSamples(&samples[0], samples.size(), 1, SAMPLE_RATE);
        soundMap[i] = buffer;
    }
}

void Sound::playSound(int height)
{
    sound.setBuffer(soundMap[height]);
    sound.play();
}

void Sound::stopSound()
{
    sound.stop();
}