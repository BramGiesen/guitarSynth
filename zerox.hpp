//
//  zerox.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 05-06-18.
//

#ifndef zerox_hpp
#define zerox_hpp

#include <stdio.h>
#include <iostream>

class Zerox
{
public:
    Zerox();
    ~Zerox();
    void calculate(double aSignal);
    
private:
    double aSignal = 0;
    double previousSignal = 0;
    double zeroCrossingPerSec = 0;
    double zeroxRate = 0;
    double phase = 0;
    double zeroxOut = 0;
    double count = 0;
    int samplerate = 44100;
    double signalVectorSize = 128;
    int n = 0;
};

#endif /* zerox_hpp */
