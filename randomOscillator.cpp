//
//  randomOscillator.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#include "randomOscillator.hpp"

//constructors and destructor
RandomGenerator::RandomGenerator(double samplerate): RandomGenerator(samplerate, 0, 0)
{
    
}

RandomGenerator::RandomGenerator(double samplerate, double frequency) : RandomGenerator(samplerate, frequency, 0)
{
    
}
RandomGenerator::RandomGenerator(double samplerate, double frequency, double phase): Oscillator (samplerate, frequency, phase)
{
    
}

RandomGenerator::~RandomGenerator()
{
    
}

void RandomGenerator::calculate()
{
    if(phase > 0.9 && notSet){
        randomValue = rand() % 100;
    }
    sample = randomValue;
}
