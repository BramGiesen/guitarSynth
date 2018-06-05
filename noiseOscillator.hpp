//
//  noiseOscillator.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 05-06-18.
//

#ifndef noiseOscillator_hpp
#define noiseOscillator_hpp

#include <stdio.h>
#include "oscillater.hpp"


class NoiseOscillator : public Oscillator
{
public:
    
    //constructors and destructor
    NoiseOscillator();
    ~NoiseOscillator();
    
    //override calculate
    //this method contains the sample calculation
    void calculate() override;
    
    
};

#endif /* noiseOscillator_hpp */
