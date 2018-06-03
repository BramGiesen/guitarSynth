//
//  signalAverage.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 03-06-18.
//

#include "signalAverage.hpp"
#include <cmath>
#include <iostream>

SignalAverage::SignalAverage(double sampleInterval)
{
    this->sampleInterval = sampleInterval;
}

SignalAverage::~SignalAverage()
{
}

double SignalAverage::getAverage()
{
    return averageSignal;
}

void SignalAverage::calculate(double signal)
{
    if( n <sampleInterval ){
        absoluteSignal = std::abs(signal);
        addedResult = absoluteSignal + addedResult;
        n++;
    }else{
        n = 0;
        averageSignal = addedResult / sampleInterval;
    }
}

