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
    void setAttackReleaseValue(double frequency);
private:
    double signal = 0.0;
    double envelope = 0.0;
    double averageSignal = 0.0;
    OnePole *lowPass = new OnePole(10 / 44100.0);
    SignalAverage *svg = new SignalAverage(20.0);
    
};

#endif /* envelopeFollower_hpp */
