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
    //get averige over n samples
    if( n <sampleInterval ){
        //take absolute value of the signal
        absoluteSignal = std::abs(signal);
        addedResult = absoluteSignal + addedResult;
        n++;
    }else{
        n = 0;
        //if n samples are added it gets divided by n samples(sample interval)
        averageSignal = addedResult / sampleInterval;
        addedResult = 0.0;
    }
}

