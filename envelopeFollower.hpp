//
//  envelopeFollower.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 03-06-18.
//

#ifndef envelopeFollower_hpp
#define envelopeFollower_hpp

#include <stdio.h>
#include "onepole.h"
#include "signalAverage.hpp"

class EnvelopeFollower
{
public:
    EnvelopeFollower();
    ~EnvelopeFollower();
    double process(double signal);
private:
    double signal = 0;
    double envelope;
    OnePole *lowPass = new OnePole(1.0 / 44100);
    SignalAverage *svg = new SignalAverage(20);
    
};

#endif /* envelopeFollower_hpp */
