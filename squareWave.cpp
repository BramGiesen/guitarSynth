//
//  squareWave.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 09-06-18.
//

#include "squareWave.hpp"

//constructors and destructor
SquareWave::SquareWave(double samplerate): SquareWave(samplerate, 0, 0)
{
    
}

SquareWave::SquareWave(double samplerate, double frequency) : SquareWave(samplerate, frequency, 0)
{
    
}

SquareWave::SquareWave(double samplerate, double frequency, double phase): Oscillator (samplerate, frequency, phase)
{
    
}

SquareWave::~SquareWave()
{
    
}


void SquareWave::calculate()
{
    sample = sin(phase * PI_2 );
    sample = (sample > 0 ) ? 1 : 0;
}
