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
    //it compares the current signal with the previous signal. If one is positif and the other negatif it detects a
    //zero crossing
    if(count < signalVectorSize){
        if((aSignal >= 0.0 && previousSignal <= 0.0)||(aSignal <= 0.0 && previousSignal >= 0.0))
        {
            zeroxRate += 1.0;
            previousSignal = aSignal;
        }
        count++;
    } else {
    zeroxOut = (zeroxRate >= 2.0) ? 2 : 1;
    zeroxRate = 0.0;
    count = 0;
    }
}

int Zerox::getZerox()
{
    return zeroxOut;
}
