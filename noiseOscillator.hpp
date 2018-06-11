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
    NoiseOscillator();
    ~NoiseOscillator();
    
    void calculate() override;
    
    
};

#endif /* noiseOscillator_hpp */
