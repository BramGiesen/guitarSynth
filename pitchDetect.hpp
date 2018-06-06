//
//  pitchDetect.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 06-06-18.
//

#ifndef pitchDetect_hpp
#define pitchDetect_hpp

#include <stdio.h>

//#include "utils.h"
//#define PROG_HAS_PITCH 1
//#define PROG_HAS_OUTPUT 1
//#define PROG_HAS_SILENCE 1
//#define PROG_HAS_JACK 1
//#include "parse_args.h"

#include <stdio.h>
#include "/Users/BramGiesen/Documents/HKU/aubio-0.4.5.darwin_framework/aubio.framework/Headers/aubio.h"

class PitchDetect
{
public:
    PitchDetect();
    ~PitchDetect();
    void process();
    void process_block(fvec_t * ibuf, fvec_t * obuf);
    void process_print (void);
    private:
        aubio_pitch_t *o;
        aubio_wavetable_t *wavetable;
        fvec_t *pitch;
};

#endif /* pitchDetect_hpp */
