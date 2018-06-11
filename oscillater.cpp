#include "oscillater.hpp"



Oscillator::Oscillator(double samplerate, double frequency, double phase) :
frequency(frequency), phase(phase), sample(0), samplerate(samplerate)
{

}

Oscillator::~Oscillator()
{
    
}

double Oscillator::getSample() { return sample; }

void Oscillator::tick()
{
    phase += frequency / samplerate;
    //keeps phase between 0 and 1;
    if(phase >= 1) phase = phase - 1;
    
    //calculate a new sample
    calculate();
}

void Oscillator::setPhase(double phase)
{
    this->phase = phase;
}


void Oscillator::setFrequency(double frequency)
{
    this->frequency = frequency;
}

double Oscillator::getFrequency() { return frequency; }
