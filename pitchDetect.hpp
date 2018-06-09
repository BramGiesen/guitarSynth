//
//  pitchDetect.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 06-06-18.
//

#ifndef pitchDetect_hpp
#define pitchDetect_hpp



//#include "utils.h"
//#define PROG_HAS_PITCH 1
//#define PROG_HAS_OUTPUT 1
//#define PROG_HAS_SILENCE 1
//#define PROG_HAS_JACK 1
//#include "parse_args.h"

#include <iostream>
#include <stdio.h>
#include "/Users/BramGiesen/Documents/HKU/aubio-0.4.5.darwin_framework/aubio.framework/Headers/aubio.h"

class PitchDetect
{
public:
    PitchDetect(float *juceInbuf);
    ~PitchDetect();
    void process();
private:
    float *juceInbuf;

};

#endif /* pitchDetect_hpp */
