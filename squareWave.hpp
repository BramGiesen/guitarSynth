//
//  squareWave.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 09-06-18.
//

#ifndef squareWave_hpp
#define squareWave_hpp

#include <stdio.h>
#include "oscillater.hpp"

class SquareWave : public Oscillator
{
public:
    
    //constructors and destructor
    SquareWave(double samplerate);
    SquareWave(double samplerate, double frequency);
    SquareWave(double samplerate, double frequency, double phase);
    ~SquareWave();
    SquareWave() = delete;
    void calculate() override;
};

#endif /* squareWave_hpp */
