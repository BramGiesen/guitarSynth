//
//  attackReleaseEnvelope.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#include "attackReleaseEnvelope.hpp"

AttackReleaseEnvelope::AttackReleaseEnvelope() : AttackReleaseEnvelope(0,0)
{
    
}

AttackReleaseEnvelope::AttackReleaseEnvelope(double attackTime, double releaseTime) : delayBuffer(100, 0)
{
    
}

AttackReleaseEnvelope::~AttackReleaseEnvelope()
{
    
}

void AttackReleaseEnvelope::setAttack(double newAttacktime)
{
    attackRate = 1 / newAttacktime / sampleRate;
}

void AttackReleaseEnvelope::setRelease(double releaseTime)
{
    this->releaseTime = releaseTime;
}

double AttackReleaseEnvelope::process(double signal)
{
    //get averige of the absolute value of the signal
    sigAve.calculate(signal);
    averigeSingal = sigAve.getAverage();
    
    delayBuffer[bufferIndex+10] = averigeSingal;
    
    //onset detection
    if(delayBuffer[bufferIndex+10] < 0.1){
        state = env_attack;
    }
    
    //attack - release envelope
    switch (state) {
        case env_idle:
            break;
        case env_attack:
            output = attackRate + output;
            
            if (output >= 1.0) {
                output = 1.0;
                state = env_sustain;
            }
        case env_sustain:
            
            if(output < 0.5){
                state = env_release;
            }
        //lowpass signal to get a longer release
        case env_release:
            output = lowpass.process(output);
            
            if (output <= 0.0) {
                output = 0.0;
                state = env_idle;
            }
    }
    
    
    envOutput = delayBuffer[bufferIndex] * output;
    
    bufferIndex++;
    bufferIndex = bufferIndex % 100;
    
    return envOutput;
}
