//
//  biquad.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 28-05-18.
//

#ifndef biquad_hpp
#define biquad_hpp

#include <stdio.h>
#include <vector>

class Biquad
{
public:
    Biquad(double peakGainDB, double Fc, double Q);
    ~Biquad();
    double process(int channel, double signal);

private:
    int type;
    double a0, a1, a2, b1, b2;
    double Fc, Q, peakGain;
    double z1, z2;
    double gain = 1.0;
    double signal = 0.0;
    double output = 0.0;
    std::vector<std::vector<std::vector<double> > > channelBuffer;

};


#endif /* biquad_hpp */
