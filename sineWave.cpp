//
//  sineWave.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 03-06-18.
//

#include "sineWave.hpp"

//Constructors and destructor
SineWave::SineWave(double samplerate) : SineWave(samplerate, 0, 0) {}

SineWave::SineWave(double samplerate, double frequency) :
SineWave(samplerate, frequency, 0) {}

SineWave::SineWave(double samplerate, double frequency, double phase) :
Oscillator (samplerate, frequency, phase) {}

SineWave::~SineWave() {}


void SineWave::calculate()
{
    sample = sin(phase * PI_2 );
}
