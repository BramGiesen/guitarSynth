//
//  sawWave.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#include "sawWave.hpp"

SawWave::SawWave(double samplerate) : SawWave(samplerate, 0, 0)
{
    
}

SawWave::SawWave(double samplerate, double frequency) : SawWave(samplerate, frequency, 0)
{
    
}

SawWave::SawWave(double samplerate, double frequency, double phase): Oscillator (samplerate, frequency, phase)
{
    
}

SawWave::~SawWave()
{
    
}


void SawWave::calculate()
{
    //non band-limited sawWave for the LFO
    sample = phase;
}





