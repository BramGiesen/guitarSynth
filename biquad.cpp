//
//  biquad.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 28-05-18.
//

#include "biquad.hpp"
#include <iostream>
#include <math.h>

Biquad::Biquad(double peakGainDB, double Fc, double Q) : channelBuffer(2, std::vector<std::vector<double> > (2, std::vector<double>(3,0)))
{
    //calculate filters coefs, I got the formula from a example written by Nigel Redmon
    double norm;
    double K = tan(M_PI * Fc);
    norm = 1 / (1 + K / Q + K * K);
    a0 = K / Q * norm;
    a1 = 0;
    a2 = -a0;
    b1 = 2 * (K * K - 1) * norm;
    b2 = (1 - K / Q + K * K) * norm;
    
}

Biquad::~Biquad()
{
    
}

//biquad uses 3d vectors to write the different data in; channelBuffer[<channel>][<delayBuffer>][<delay index>]
//It has two vectors(channel) that contain two delaybuffers each. each delay buffer has a lenght of 3
double Biquad::process(int channel, double input)
{
    
    channelBuffer[channel][0][0] = input;
    
    channelBuffer[channel][1][0] = a0 * channelBuffer[channel][0][0] + a1 * channelBuffer[channel][0][1] + a2 * channelBuffer[channel][0][2] - b1 * channelBuffer[channel][1][1] - b2 *  channelBuffer[channel][1][2];
    
    //move the samples one place
    for(int index = 0 ; index < 2 ; index++){
        for (int bufferSize = 2; bufferSize >=1; bufferSize--){
            channelBuffer[channel][index][bufferSize] = channelBuffer[channel][index][bufferSize-1];
        }
    }
    
    
    return channelBuffer[channel][1][0];
}



