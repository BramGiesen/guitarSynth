//
//  envelopeFollower.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 03-06-18.
//

#include <stdio.h>
#include "envelopeFollower.hpp"

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
    return envelope;
}
