//
//  signalAverage.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 03-06-18.
//

#ifndef signalAverage_hpp
#define signalAverage_hpp

#include <stdio.h>
#include <cmath>

class SignalAverage
{
public:
    SignalAverage(double sampleInterval);
    ~SignalAverage();
    void calculate(double signal);
    double getAverage();
private:
    int n = 0;
    double averageSignal = 0;
    double sampleInterval;
    double absoluteSignal = 0;
    double addedResult = 0;
};
#endif /* signalAverage_hpp */
