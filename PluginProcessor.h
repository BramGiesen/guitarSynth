/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <thread>
#include <math.h>

#include "../JuceLibraryCode/JuceHeader.h"
#include "biquad.hpp"
#include "/Users/BramGiesen/aubio-0.4.5.darwin_framework/aubio.framework/Headers/aubio.h"
#include "envelopeFollower.hpp"
#include "zerox.hpp"
#include "selector.hpp"
#include "signalAverage.hpp"
#include "Synthesizer.hpp"

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
    double  applyDistortion(double signal);
    
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void updateFrequency();

    void setFrequency();
    void setWaveForm();
    void updateSynth();
    
    void applyAmplitude();
    
    
    //==============================================================================
    
    AudioPlayHead::CurrentPositionInfo lastPosInfo;
    
    
    int lastUIWidth = 400, lastUIHeight = 200;
    
    // Our parameters
    AudioParameterFloat* glideParam = nullptr;
    AudioParameterFloat* driveParam = nullptr;
    AudioParameterFloat* rangeParam = nullptr;
    AudioParameterFloat* fmRatioParam = nullptr;
    AudioParameterFloat* fmModDepthParam = nullptr;
    AudioParameterFloat* attackReleaseParam = nullptr;
    AudioParameterFloat* amplitudeParam = nullptr;
    AudioParameterFloat* LFOfrequencyParam = nullptr;
    AudioParameterFloat* LFOdepthParam = nullptr;
    AudioParameterChoice* waveFormParam;
    
    
    // Current track colour and name
    TrackProperties trackProperties;
private:
    
    //variables
    
    //==FM===================
    double fmFrequency = 0.0;
    double synthFrequency = 0.0;
    double synthSample = 0.0;
    double oscillatorFreq = 0.0;
    
    //==FILTERS==============
    float filterSignal1 = 0.0;
    float filterSignal2 = 0.0;
    float firstFilterSignal[15];
    float addedfilterSignal1;
    double lastSampleRate;
    
    //distortion
    double drive = 1;
    double range = 1;
    double signalDistortion = 0;
    double blend = 1;
    
    //vectors & arrays========
    std::vector<double> envFollowValues;
    std::vector<double> filterFreqs = {175.0,220.0,265.0,345.0,550.0,700.0,880.0,1000.0, 1100.0, 1400.0, 1750.0,2300.0,2950.0, 3500.0, 4300.0};
    
    
    //objects=================
    Zerox zerox;
    Selector selector;
    
    //Object pointers=========
    Synth *synth;
    Oscillator **oscillators;
    Biquad **bandPassFilters;
    EnvelopeFollower **envelopeFollowers;
    OnePole *lowPass;
    OnePole *envlowPass;
    OnePole *LFOlowPass;
    
    //is used for ringbuffer: audioBufferPitch
    int x = 0;
    
    //aubio===================================================================
 
    int lenghtOfAudioBuffer = 4096.0/4.0;
    float audioBufferPitch[(4096/4)];
    
    //variables
    uint_t win_s = 4096.0; // window size
    uint_t hop_s = win_s / 4.0; // hop size
    smpl_t pitchdetected = 0.0;
    double addedFreqs = 0.0;
    
    bool init = false;
    //TODO make flexible
    uint_t samplerate = 44100.0; // samplerate
    
    //vectors for aubio
    fvec_t *input = new_fvec (hop_s); // input buffer
    fvec_t *out = new_fvec (1); // output candidates
    // create pitch object
    aubio_pitch_t *o = new_aubio_pitch ("default", win_s, hop_s, samplerate);
    
    double detectedPitches[20000];
    double mostDetected = 0;
    
    //pitch detection thread
    std::thread pitchDetectThread;
    
    
    double sampleRate = 0;
    double phase = 0;
    double sineWave = 0;
    double LFO = 0;
    float amplitudeWet = 0;
    float amplitudeDry = 0;
    int previousI = 1;
    float glide = 0;
    float syncfreq = 0;
    float beats = 120;
    double startLoop = 0;
    
    int LFOI = 0;
    float LFOf = 0;
    float previousLFOfreq = 0;
    float LFOP = 0;
    float lowpassParam = 0;
    
    bool startTimeSet = false;
    bool initWaveform = false;
    bool setPhase = false;
    bool setPhaseSwitch = false;
    
    
    float rateValues[11]{15,20,30,40,60,80,120,160.0000000001,240,320.0000000002,480};
    void setBPM(AudioPlayHead::CurrentPositionInfo bpm);
    void setOSCphase(AudioPlayHead::CurrentPositionInfo bpm);
    void updateCurrentTimeInfoFromHost();
    
    

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSynth_2AudioProcessor)
};
