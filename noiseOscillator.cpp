//
//  noiseOscillator.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 05-06-18.
//

#include "noiseOscillator.hpp"
#include <stdlib.h>


NoiseOscillator::NoiseOscillator() : Oscillator (44100, 440, 0)
{
    
}

NoiseOscillator::~NoiseOscillator() {}


void NoiseOscillator::calculate()
{
    //gives random value's to create a noise oscillator
    sample = (rand() % 2) -1;
    
}
