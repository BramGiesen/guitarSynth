//
//  pitchDetect.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 06-06-18.
//

#include "pitchDetect.hpp"

PitchDetect::PitchDetect(float *juceInbuf)
{
    this->juceInbuf = juceInbuf;
    
    pitch_detector = new_aubio_pitch((char *)pitch_method,anachunksize,hopsize,samplerate);
    if (pitch_tolerance != 0.)
        aubio_pitch_set_tolerance(pitch_detector,pitch_tolerance);
    if (silence_threshold != -90.)
        aubio_pitch_set_silence(pitch_detector,silence_threshold);
    if (pitch_unit != NULL)
        aubio_pitch_set_unit(pitch_detector,(char *)pitch_unit);
    
    pitch = new_fvec(1);
    
    pitchInbuf = pitchArray;
    
}

PitchDetect::~PitchDetect()
{
    
}

void PitchDetect::process()
{
    // lever audio input aan via een buffer met samples
    anabuffer->data = pitchInbuf;
    
    // perform next pitch scan
    aubio_pitch_do(pitch_detector,anabuffer,pitch);
    smpl_t pitch_found = fvec_get_sample(pitch,0);
    
    std::cout << "pitch = " << pitch << std::endl;
    
}



