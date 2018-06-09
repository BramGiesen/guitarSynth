/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "biquad.hpp"
#include "/Users/BramGiesen/aubio-0.4.5.darwin_framework/aubio.framework/Headers/aubio.h"
#include "envelopeFollower.hpp"
#include "sineWave.hpp"
#include "noiseOscillator.hpp"
#include "zerox.hpp"
#include "selector.hpp"
#include <thread>

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
    
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    void updateFrequency();
    void updateFilter();

    AudioParameterChoice* waveFormParam;
private:
    //variables
    double modDepth = 100;
    double ratio = 1;
    double fmFrequency = 0;
    
    float filterSignal1 = 0;
    float filterSignal2 = 0;
    float firstFilterSignal[15];
    float addedfilterSignal1;
    float addedfilterSignal2;
    double lastSampleRate;
    
    //vectors & arrays
    std::vector<double> envFollowValues;
    std::vector<double> filterFreqs = {175.0,220.0,265.0,345.0,550.0,700.0,880.0,1000.0, 1100.0, 1400.0, 1750.0,2300.0,2950.0, 3500.0, 4300.0};
    
    
    //objects
    Zerox zerox;
    Selector selector;

    //Object pointers
    Oscillator **oscillators;
    Biquad **bandPassFilters;
    EnvelopeFollower **envelopeFollowers;
    OnePole *lowPass = new OnePole(1.0 / 44100);
    
    int x = 0;
    
    //aubio===================================================================
 
    int lenghtOfAudioBuffer = 2048/4;
    float audioBufferPitch[(2048/4)];
    
    // 1. allocate some memory
    uint_t win_s = 2048; // window size
    uint_t hop_s = win_s / 4; // hop size
    uint_t samplerate = 44100; // samplerate
    // create some vectors
    fvec_t *input = new_fvec (hop_s); // input buffer
    fvec_t *out = new_fvec (1); // output candidates
    // create pitch object
    aubio_pitch_t *o = new_aubio_pitch ("default", win_s, hop_s, samplerate);
    
    smpl_t pitchdetected = 0;
    
    //pitch thread
    std::thread pitchDetectThread;

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSynth_2AudioProcessor)
};
