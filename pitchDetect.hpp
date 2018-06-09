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
    float samplerate = 44100;
    float *juceInbuf;
    float *pitchInbuf;
    //--------- variabelen
    float pitchArray[1024];
    // grootte van analyse buffer. Wordt ergens anders bepaald, zet bv. op 1024
    // of wat jij nodig hebt
    unsigned int anachunksize = 1000024;
    
    // hopsize: grootte van sprongen door de oorspronkelijke audio heen
    unsigned int hopsize = 1;
    
    aubio_pitch_t *pitch_detector;
    fvec_t *pitch;
    aubio_onset_t *onset_detector;
    fvec_t *onset;
    
    fvec_t *anabuffer;
    
    
    /*
     * pitch detector configuration
     */
    
    const char_t *pitch_method = "yin";
    const char_t *pitch_unit = "freq";
    smpl_t pitch_tolerance = 0.1;
    smpl_t silence_threshold = -90.;
};

#endif /* pitchDetect_hpp */
