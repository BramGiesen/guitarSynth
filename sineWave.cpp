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

//override calculate method
//this method contains the sample calculation
void SineWave::calculate()
{
    //NOTE sin() method is not the most efficient way to calculate the sine value
    sample = sin(phase * PI_2 );
//    sample = (sinus > 0 ) ? 1 : 0;
    //std::cout << "\n" << phase  << "PI_2 " << "\n" ;
}
