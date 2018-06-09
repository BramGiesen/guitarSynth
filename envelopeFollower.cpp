//
//  envelopeFollower.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 03-06-18.
//

#include <stdio.h>
#include "envelopeFollower.hpp"
#include <iostream>

EnvelopeFollower::EnvelopeFollower()
{
    
}
 EnvelopeFollower::~EnvelopeFollower()
{
    delete lowPass;
    lowPass = nullptr;
    delete svg;
    svg = nullptr;
}

double EnvelopeFollower::process(double signal)
{
    svg->calculate(signal);
    envelope = lowPass->process(svg->getAverage());
    // KIJK hier nog naar! 
    envelope = (envelope < 0.000001) ? 0.0 : envelope;
    return envelope * 100.0;
}
