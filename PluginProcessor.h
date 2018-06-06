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
#include "pitchDetect.hpp"

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
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void updateFilter();

    AudioParameterChoice* waveFormParam;
private:
    float filterSignal1 = 0;
    float filterSignal2 = 0;
    float firstFilterSignal[15];
    std::vector<double> envFollowValues;
    Oscillator **oscillators;
    std::vector<double> vec = {10,20};
//    EnvelopeFollower envFollow;
    Zerox zerox;
    Selector selector;
    SineWave *sin =  new SineWave(44100.0, 10.0 , 0.0);
    Biquad **bandPassFilters;
    
    PitchDetect pitch;

    EnvelopeFollower **envelopeFollowers;
    std::vector<double> filterFreqs = {175.0,220.0,265.0,345.0,550.0,700.0,880.0,1000.0, 1100.0, 1400.0, 1750.0,2300.0,2950.0, 3500.0, 4300.0};
    
    float addedfilterSignal;
    double lastSampleRate;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSynth_2AudioProcessor)
};
