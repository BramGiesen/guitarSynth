/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
                       ), envFollowValues(15,0)
#endif
{
    addParameter (waveFormParam = new AudioParameterChoice ("Wave_form", "LFO_wave form", { "rising saw", "falling saw", "sine", "square", "noise generator" }, 4));
    
    
}

GuitarSynth_2AudioProcessor::~GuitarSynth_2AudioProcessor()
{
    delete sin;
    sin = nullptr;
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
    
    oscillators = new Oscillator*[2];
    
    oscillators[0] = new SineWave(lastSampleRate, 110, 0);
    oscillators[1] = new NoiseOscillator();
    
    bandPassFilters = new Biquad*[30];
    
    
    for (int i = 0; i < 30; i++){
        bandPassFilters[i] = new Biquad(1.0, filterFreqs[i % 15] / lastSampleRate, 40.0);
    }

    envelopeFollowers = new EnvelopeFollower*[15];

    for (int i = 0; i < 15; i++){
        envelopeFollowers[i] = new EnvelopeFollower;
    }

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
        
        for (int channel = 0; channel< totalNumInputChannels; ++channel)
        {
            auto channelData = buffer.getWritePointer (channel);
            float  signal = buffer.getSample(channel, sample);
            
            //zerox analysis
            for (int filterIndex = 0; filterIndex < 15; filterIndex++){
                filterSignal2 = bandPassFilters[filterIndex]->process(channel, signal);
                envFollowValues[filterIndex] = envelopeFollowers[filterIndex]->process(filterSignal2);
            }

            //envelope follower
            zerox.calculate(signal);
            int oscIndex = zerox.getZerox() - 1;
            double synthSample = oscillators[oscIndex]->getSample();
            

            oscillators[0]->tick();
            oscillators[1]->tick();
            
            //Synthsignal + filters and envelope follower
            for (int filterIndex = 0; filterIndex < 15; filterIndex++){
                float filterSignal = bandPassFilters[filterIndex + 15]->process(channel, synthSample);
                addedfilterSignal = (filterSignal * envFollowValues[filterIndex]) + addedfilterSignal;
            }
            
            channelData[sample] = addedfilterSignal;
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
