//
//  pitchDetect.cpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 06-06-18.
//

#include "pitchDetect.hpp"

PitchDetect::PitchDetect()
{
    
}

PitchDetect::~PitchDetect()
{
    
}

void PitchDetect::process_block(fvec_t * ibuf, fvec_t * obuf)
{
//    smpl_t freq;
//    aubio_pitch_do (o, ibuf, pitch);
//    if ( !usejack && ! sink_uri ) return;
//    fvec_zeros(obuf);
//    freq = fvec_get_sample(pitch, 0);
//    aubio_wavetable_set_amp ( wavetable, aubio_level_lin (ibuf) );
//    aubio_wavetable_set_freq ( wavetable, freq );
//    if (mix_input)
//        aubio_wavetable_do (wavetable, ibuf, obuf);
//    else
//        aubio_wavetable_do (wavetable, obuf, obuf);
}

void PitchDetect::process_print (void)
{
//    smpl_t pitch_found = fvec_get_sample(pitch, 0);
//    print_time(blocks * hop_size);
//    outmsg(" %f\n", pitch_found);
}

void PitchDetect::process()
{
//    examples_common_init(argc,argv);
//
//    verbmsg ("using source: %s at %dHz\n", source_uri, samplerate);
//    verbmsg ("pitch method: %s, ", pitch_method);
//    verbmsg ("pitch unit: %s, ", pitch_unit);
//    verbmsg ("buffer_size: %d, ", buffer_size);
//    verbmsg ("hop_size: %d, ", hop_size);
//    verbmsg ("tolerance: %f\n", pitch_tolerance);
//
//    o = new_aubio_pitch (pitch_method, buffer_size, hop_size, samplerate);
//    if (o == NULL) { ret = 1; goto beach; }
//    if (pitch_tolerance != 0.)
//        aubio_pitch_set_tolerance (o, pitch_tolerance);
//    if (silence_threshold != -90.)
//        aubio_pitch_set_silence (o, silence_threshold);
//    if (pitch_unit != NULL)
//        aubio_pitch_set_unit (o, pitch_unit);
//
//    pitch = new_fvec (1);
//
//    wavetable = new_aubio_wavetable (samplerate, hop_size);
//    aubio_wavetable_play ( wavetable );
//
//    examples_common_process((aubio_process_func_t)process_block,process_print);
//
//    del_aubio_pitch (o);
//    del_aubio_wavetable (wavetable);
//    del_fvec (pitch);
//
//beach:
//    examples_common_del();
//    return ret;
}

