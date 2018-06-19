//
//  envelopeFollower.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 03-06-18.
//

#include <stdio.h>
#include "envelopeFollower.hpp"
#include <iostream>

EnvelopeFollower::EnvelopeFollower(double sampleRate) : sampleRate(sampleRate)
{
    lowPass = new OnePole(10 /  sampleRate);
    svg = new SignalAverage(20.0);
}
 EnvelopeFollower::~EnvelopeFollower()
{
    delete lowPass;
    lowPass = nullptr;
    delete svg;
    svg = nullptr;
}

//set low pass frequency, I use it to get different attack and release times
void EnvelopeFollower::setAttackReleaseValue(double frequency)
{
    lowPass->setFc(frequency/44100);
}

double EnvelopeFollower::process(double signal)
{
    //calculate average signal
    svg->calculate(signal);
    //get average signal
    averageSignal = svg->getAverage();
    //low pass the averige signal, to make it smoother. I also use the low pass to adjust the attack and release of the synth
    envelope = lowPass->process(averageSignal);
    envelope *= 100.0;
    envelope = (envelope > 0.01) ? 0.01 : envelope;
//    std::cout << "envelope = " << envelope << std::endl;
    return envelope;
}
