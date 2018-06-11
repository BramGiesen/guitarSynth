//
//  fallingSaw.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#include "fallingSaw.hpp"

InvertedSawWave::InvertedSawWave(double samplerate): InvertedSawWave(samplerate, 0, 0)
{
    
}

InvertedSawWave::InvertedSawWave(double samplerate, double frequency) : InvertedSawWave(samplerate, frequency, 0)
{
    
}
InvertedSawWave::InvertedSawWave(double samplerate, double frequency, double phase): Oscillator (samplerate, frequency, phase)
{
    
}

InvertedSawWave::~InvertedSawWave()
{
    
}

 void InvertedSawWave::calculate()
{
    //inverted non-bandlimited saw for LFO
    sample = phase *-1 + 1;
}

