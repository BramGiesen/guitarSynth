//
//  sineWave.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 03-06-18.
//

#ifndef sineWave_hpp
#define sineWave_hpp

#include <stdio.h>
#include "oscillater.hpp"

class SineWave : public Oscillator
{
public:
    
    //constructors and destructor
    SineWave(double samplerate);
    SineWave(double samplerate, double frequency);
    SineWave(double samplerate, double frequency, double phase);
    ~SineWave();
    //prevent the default constructor to be generated
    SineWave() = delete;
    
    //override calculate
    //this method contains the sample calculation
    void calculate() override;
    
    
};

#endif /* sineWave_hpp */
