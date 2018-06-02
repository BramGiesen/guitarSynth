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
    Biquad *bandpass175 = new Biquad(1.0, 174.0 / 44100.0, 40.0);
    Biquad *bandpass220 = new Biquad(1.0, 220.0 / 44100.0, 40.0);
    Biquad *bandpass265 = new Biquad(1.9, 265.0 / 44100.0, 40.0);
   
    
   
//
//    Biquad bandpassL(1, 220, 40);
//    Biquad bandpassR(1, 220, 40);
//    Biquad bandpass1L(1, 265, 40);
//    Biquad bandpass1R(1, 265, 40);
    
    
    float lastSampleRate;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSynth_2AudioProcessor)
};
