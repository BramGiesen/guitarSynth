//
//  sawWave.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#ifndef sawWave_hpp
#define sawWave_hpp

#include <stdio.h>
#include "oscillater.hpp"

class SawWave : public Oscillator
{
public:
    SawWave(double samplerate);
    SawWave(double samplerate, double frequency);
    SawWave(double samplerate, double frequency, double phase);
    ~SawWave();
    //prevent the default constructor to be generated
    SawWave() = delete;
    
    //override calculate
    //this method contains the sample calculation
    void calculate() override;
    
    
};


#endif /* sawWave_hpp */
