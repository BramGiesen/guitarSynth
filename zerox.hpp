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
    int getZerox();
    
private:
    double aSignal = 0.0;
    double previousSignal = 0.0;
    double zeroCrossingPerSec = 0.0;
    double zeroxRate = 0.0;
    double phase = 0.0;
    double zeroxOut = 1.0;
    double count = 0.0;
    int samplerate = 44100.0;
    double signalVectorSize = 128.0;
    int n = 0;
};

#endif /* zerox_hpp */
