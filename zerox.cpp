//
//  zerox.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 05-06-18.
//

#include "zerox.hpp"

Zerox::Zerox()
{
    
}

Zerox::~Zerox()
{
    
}

void Zerox::calculate(double aSignal)
{
    if(count < signalVectorSize){
        if((aSignal >= 0 && previousSignal <= 0)||(aSignal <= 0 && previousSignal >= 0))
        {
            zeroxRate += 1;
            previousSignal = aSignal;
        }
        count++;
    } else {
    zeroxOut = (zeroxRate >= 2) ? 2 : 1;
    zeroxRate = 0;
    count = 0;
    }
}

int Zerox::getZerox()
{
    return zeroxOut;
}
