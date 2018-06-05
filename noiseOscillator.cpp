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
    //NOTE sin() method is not the most efficient way to calculate the sine value
    sample = (rand() % 2) -1;
    //std::cout << "\n" << phase  << "PI_2 " << "\n" ;
}
