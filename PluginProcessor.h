/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <thread>

#include "../JuceLibraryCode/JuceHeader.h"
#include "biquad.hpp"
#include "/Users/BramGiesen/aubio-0.4.5.darwin_framework/aubio.framework/Headers/aubio.h"
#include "envelopeFollower.hpp"
#include "sineWave.hpp"
#include "noiseOscillator.hpp"
#include "zerox.hpp"
#include "selector.hpp"
#include <math.h>

//==============================================================================
/**
*/
class GuitarSynth_2AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    GuitarSynth_2AudioProcessor();
    ~GuitarSynth_2AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void StartThread();
    
    void pitchDetect();
    float mtof(float aubiofreq);
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void updateFrequency();

    AudioParameterChoice* waveFormParam;
private:
    //variables
    
    //==FM===================
    double modDepth = 10.0;
    double ratio = 2.0;
    double fmFrequency = 0.0;
    double lowPassPitch = 0.0;
    
    //==FILTERS==============
    float filterSignal1 = 0.0;
    float filterSignal2 = 0.0;
    float firstFilterSignal[15];
    float addedfilterSignal1;
    float addedfilterSignal2;
    double lastSampleRate;
    
    //vectors & arrays========
    std::vector<double> envFollowValues;
    std::vector<double> filterFreqs = {175.0,220.0,265.0,345.0,550.0,700.0,880.0,1000.0, 1100.0, 1400.0, 1750.0,2300.0,2950.0, 3500.0, 4300.0};
    
    
    //objects=================
    Zerox zerox;
    Selector selector;

    //Object pointers=========
    Oscillator **oscillators;
    Biquad **bandPassFilters;
    EnvelopeFollower **envelopeFollowers;
    OnePole *lowPass = new OnePole(10.0 / 44100.0);
    
    //is used for ringbuffer: audioBufferPitch
    int x = 0;
    
    //aubio===================================================================
 
    int lenghtOfAudioBuffer = 4096.0/4.0;
    float audioBufferPitch[(4096/4)];
    
    //variables
    uint_t win_s = 4096.0; // window size
    uint_t hop_s = win_s / 4.0; // hop size
    smpl_t pitchdetected = 0.0;
    
    //TODO make flexible
    uint_t samplerate = 44100.0; // samplerate
    
    //vectors for aubio
    fvec_t *input = new_fvec (hop_s); // input buffer
    fvec_t *out = new_fvec (1); // output candidates
    // create pitch object
    aubio_pitch_t *o = new_aubio_pitch ("default", win_s, hop_s, samplerate);
    
    
    //pitch detection thread
    std::thread pitchDetectThread;

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSynth_2AudioProcessor)
};
