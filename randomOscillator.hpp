//
//  randomOscillator.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#ifndef randomOscillator_hpp
#define randomOscillator_hpp


#include <stdio.h>
#include <cstdlib>
#include "oscillater.hpp"


class RandomGenerator : public Oscillator
{
public:
    RandomGenerator(double samplerate);
    RandomGenerator(double samplerate, double frequency);
    RandomGenerator(double samplerate, double frequency, double phase);
    ~RandomGenerator();
    RandomGenerator() = delete;
    
    void calculate() override;
    
private:
    bool notSet=true;
    int randomValue = 0;
    
    
};



#endif /* randomOscillator_hpp */
