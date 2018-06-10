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
    
    //constructors and destructor
    RandomGenerator(double samplerate);
    RandomGenerator(double samplerate, double frequency);
    RandomGenerator(double samplerate, double frequency, double phase);
    ~RandomGenerator();
    //prevent the default constructor to be generated
    RandomGenerator() = delete;
    
    //override calculate
    //this method contains the sample calculation
    void calculate() override;
    
private:
    bool notSet=true;
    int randomValue = 0;
    
    
};



#endif /* randomOscillator_hpp */
