//
//  fallingSaw.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#ifndef fallingSaw_hpp
#define fallingSaw_hpp

#include <stdio.h>
#include "oscillater.hpp"

class InvertedSawWave : public Oscillator
{
public:
    InvertedSawWave(double samplerate);
    InvertedSawWave(double samplerate, double frequency);
    InvertedSawWave(double samplerate, double frequency, double phase);
    ~InvertedSawWave();
    InvertedSawWave() = delete;
    
    void calculate() override;
    
    
};

#endif /* fallingSaw_hpp */
