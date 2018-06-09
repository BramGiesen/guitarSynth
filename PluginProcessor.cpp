/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "/Users/BramGiesen/Documents/HKU/aubio-0.4.5.darwin_framework/aubio.framework/Headers/aubio.h"
#include <thread>

//==============================================================================
GuitarSynth_2AudioProcessor::GuitarSynth_2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), envFollowValues(15,0), pitchDetectThread()
#endif
{
    for(int i = 0; i < lenghtOfAudioBuffer; i++){
        audioBufferPitch[i] = 0;
    }
    
    addParameter (waveFormParam = new AudioParameterChoice ("Wave_form", "LFO_wave form", { "rising saw", "falling saw", "sine", "square", "noise generator" }, 4));
    
    //get `hop_s` new samples into `input`
    input->data = audioBufferPitch;
    
}

GuitarSynth_2AudioProcessor::~GuitarSynth_2AudioProcessor()
{
    //delete pointers
    delete bandPassFilters;
    bandPassFilters = nullptr;
    
    delete envelopeFollowers;
    envelopeFollowers = nullptr;
    
    delete oscillators;
    oscillators = nullptr;
    
    //clean up aubio
    del_aubio_pitch (o);
    del_fvec (out);
//    del_fvec (input);
    aubio_cleanup ();
    
    if(pitchDetectThread.joinable()) pitchDetectThread.join();
}

//==============================================================================
const String GuitarSynth_2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GuitarSynth_2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GuitarSynth_2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GuitarSynth_2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GuitarSynth_2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GuitarSynth_2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GuitarSynth_2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void GuitarSynth_2AudioProcessor::setCurrentProgram (int index)
{
}

const String GuitarSynth_2AudioProcessor::getProgramName (int index)
{
    return {};
}

void GuitarSynth_2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GuitarSynth_2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    
    oscillators = new Oscillator*[3];
    
    oscillators[0] = new SineWave(lastSampleRate, 220, 0);
    oscillators[1] = new NoiseOscillator();
    oscillators[2] = new SineWave(lastSampleRate, 0, 0);
    
    int numberOfBiquads = 60;
    bandPassFilters = new Biquad*[numberOfBiquads];
    
    
    for (int i = 0; i < numberOfBiquads; i++){
        bandPassFilters[i] = new Biquad(1.0, filterFreqs[i % 15] / lastSampleRate, 46.0);
    }

    envelopeFollowers = new EnvelopeFollower*[15];

    for (int i = 0; i < 15; i++){
        envelopeFollowers[i] = new EnvelopeFollower;
    }
    
    //start aubio pitch detection thread
    StartThread();

}

void GuitarSynth_2AudioProcessor::updateFilter()
{
    //update filter params
    
}

void GuitarSynth_2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GuitarSynth_2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GuitarSynth_2AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    for(int sample = 0; sample < buffer.getNumSamples(); ++sample){
        
    audioBufferPitch[x++ % lenghtOfAudioBuffer] = buffer.getSample(0, sample);
       
        for (int channel = 0; channel< totalNumInputChannels; ++channel)
        {
            auto channelData = buffer.getWritePointer (channel);
            float  signal = buffer.getSample(channel, sample);
            
            
            for (int filterIndex = 0; filterIndex < 15; filterIndex++){
                filterSignal1 = bandPassFilters[filterIndex]->process(channel, signal);
;
            }

            //filter input again and send filtered signal to envelope follower
            for (int filterIndex = 15; filterIndex < 30; filterIndex++){
                filterSignal2 = bandPassFilters[filterIndex]->process(channel, filterSignal1);
                //process envolope followers and put the return values in a vector
                envFollowValues[filterIndex-15] = 80 * envelopeFollowers[filterIndex-15]->process(filterSignal2);
            }

            //zerox analysis
            zerox.calculate(signal);
            int oscIndex = zerox.getZerox() - 1;
            double synthSample = oscillators[oscIndex]->getSample();
            
            oscillators[0]->tick();
            oscillators[1]->tick();
            oscillators[2]->tick();
            
            //Synthsignal + filters and envelope follower
            for (int filterIndex = 30; filterIndex < 45; filterIndex++){
                float filterSignal = bandPassFilters[filterIndex]->process(channel, synthSample);
                addedfilterSignal1 = filterSignal + addedfilterSignal1;
            }
            
            //filter the signal one last time
            for (int filterIndex = 45; filterIndex < 60; filterIndex++){
                float filterSignal = bandPassFilters[filterIndex]->process(channel, addedfilterSignal1);
                addedfilterSignal2 = (filterSignal * envFollowValues[filterIndex-45]) + addedfilterSignal2;
            }
            
            channelData[sample] = addedfilterSignal2;
        }
    }
}

//==============================================================================
bool GuitarSynth_2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GuitarSynth_2AudioProcessor::createEditor()
{
    return new GuitarSynth_2AudioProcessorEditor (*this);
}

void GuitarSynth_2AudioProcessor::StartThread(){
    // This will start the thread. Notice move semantics!
    pitchDetectThread = std::thread(&GuitarSynth_2AudioProcessor::pitchDetect,this);
}

void GuitarSynth_2AudioProcessor::pitchDetect()
{
    while (true){
//      exectute pitch
        aubio_pitch_do (o, input, out);
        
//      do something with output candidates
        smpl_t pitchdetected = fvec_get_sample(out, 0);
        
//        std::cout <<"output = " << pitchdetected << std::endl;
        fmFrequency = lowPass->process(pitchdetected);
//        oscillators[0]->setFrequency(lowPass->process(pitchdetected));
        
        updateFrequency();
    }

}

void GuitarSynth_2AudioProcessor::updateFrequency()
{
    oscillators[2]->setFrequency(fmFrequency * ratio);
    oscillators[0]->setFrequency(fmFrequency + ((oscillators[2]->getSample())* (modDepth * fmFrequency * ratio)));
}

//==============================================================================
void GuitarSynth_2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GuitarSynth_2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GuitarSynth_2AudioProcessor();
}
