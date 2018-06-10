#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_
#include <iostream>
#include "math.h"

#define PI_2 6.28318530717959

//TODO: fix typo in file name

class Oscillator
{
public:
    Oscillator(double samplerate, double frequency, double phase);
    virtual ~Oscillator();
    double getSample();
    void tick();
    void setFrequency(double frequency);
    void setPhase(double phase);
    double getFrequency();
protected:
    virtual void calculate() = 0;
    double frequency;
    double phase;
    double sample;
    double samplerate;
    
    
    
};

#endif
