//
//  Synthesizer.hpp
//  GuitarSynth_2
//
//  Created by Bram Giesen on 10-06-18.
//

#ifndef Synthesizer_hpp
#define Synthesizer_hpp

#include <stdio.h>

#include "oscillater.hpp"
#include "sineWave.hpp"
#include "noiseOscillator.hpp"
#include "squareWave.hpp"
#include "randomOscillator.hpp"
#include "sawWave.hpp"
#include "fallingSaw.hpp"
#include "squareWave.hpp"
#include "onepole.h"

class Synth
{
public:
    Synth(double sampleRate);
    ~Synth();
    void setPhaseLFO(double phase);
    void setGlide(double glide);
    void setLFO(int LFOnumber);
    void setLFOfreq(double LFOfreq);
    void setLFOdepth(double LFOdepth);
    void setFrequency(double frequency);
    void setRatio(float fmRatio);
    void setModDepth(float fmModDepth);
    double getLFOsample();
    double getModulatorSample();
    double mtof(double midiPitch);
    void updateFrequency();
    void processFrequency();
    void mtof();
    double process();
private:
    //variables
    double LFO = 0.0;
    double LFOfreq;
    double LFOdepth;
    double sampleRate;
    double fmRatio;
    double fmModDepth;
    double frequency;
    double sample;
    int previousWaveForm;
    double phase = 0.0;
    
    float glideValue = 0.0;
    float glide = 0.0;
    float syncfreq = 0.0;
    float beats = 120.0;
    double startLoop = 0.0;
    int LFOI = 0.0;
    float LFOf = 0.0;
    float previousLFOfreq = 0.0;
    float LFOP = 0.0;
    float lowpassParam = 0.0;
    
    //bools
    bool initWaveForm;
    bool setPhase = false;
    bool setPhaseSwitch = false;
    
    //array of values to create a beatsync LFO
    float rateValues[11]{15,20,30,40,60,80,120,160.0000000001,240,320.0000000002,480};
    
    
    //pointer array of type Oscillator
    Oscillator **oscillators;
    
    
};

#endif /* Synthesizer_hpp */
