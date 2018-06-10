//
//  attackReleaseEnvelope.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#ifndef attackReleaseEnvelope_hpp
#define attackReleaseEnvelope_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "onepole.h"
#include "signalAverage.hpp"

class AttackReleaseEnvelope
{
public:
    AttackReleaseEnvelope();
    AttackReleaseEnvelope(double attackTime, double releaseTime);
    ~AttackReleaseEnvelope();
    void setAttack(double attackTime);
    void setRelease(double releaseTime);
    double process(double signal);
private:
    enum envState {
        env_idle = 0,
        env_attack,
        env_sustain,
        env_release
    };
    
    //variables
    int state;
    double averigeSingal = 0.0;
    unsigned long bufferIndex = 1;
    double sampleRate = 44100.0;
    double attackTime;
    double attackRate;
    double releaseTime;
    double attackEnvelopeValue;
    double output = 0.0;
    double envOutput = 0.0;
    //vector
    std::vector<double> delayBuffer;
    
    //objects
    SignalAverage sigAve = 5;
    OnePole lowpass {1.0/sampleRate};
};

#endif /* attackReleaseEnvelope_hpp */
