//
//  onepole.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 03-06-18.
//

#include <stdio.h>
#include "onepole.h"

OnePole::OnePole()
{
    a0 = 1.0; b1 = 0.0; z1 = 0.0;
    
}

OnePole::OnePole(double Fc)
{
    z1 = 0.0; setFc(Fc);
}

OnePole::~OnePole()
{
    
}

void OnePole::setFc(double Fc) {
    b1 = exp(-2.0 * M_PI * Fc);
    a0 = 1.0 - b1;
}


float OnePole::process(float in) {
    return z1 = in * a0 + z1 * b1;
}
