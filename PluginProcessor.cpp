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
                       )
#endif
{
    addParameter (waveFormParam = new AudioParameterChoice ("Wave_form", "LFO_wave form", { "rising saw", "falling saw", "sine", "square", "noise generator" }, 4));
}

GuitarSynth_2AudioProcessor::~GuitarSynth_2AudioProcessor()
{
    delete bandpass175;
    bandpass175 = nullptr;
    delete bandpass220;
    bandpass220 = nullptr;
    
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
    
    
//    bandpass1L.setCoefs(0.755232, 0.,  -0.755232, 0.073769, 0.767621);
//    bandpass1R.setCoefs(0.755232, 0.,  -0.755232, 0.073769, 0.767621);
//    bandpassL.setCoefs(0.007484, 0., -0.007484, -1.996055, 0.996258);
//    bandpassR.setCoefs(0.007484, 0., -0.007484, -1.996055, 0.996258);
    
//    bandpassL->calcBandPass(1, 220, 40);
//    bandpassR->calcBandPass(1, 220, 40);
 
    
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

    
    //    TODO: check if it is stereo or mono
    
    for(int sample = 0; sample < buffer.getNumSamples(); ++sample){
        
        
        auto channelDataL = buffer.getWritePointer (0);
        auto channelDataR = buffer.getWritePointer (1);
        float  signalR = buffer.getSample(1, sample);
        float  signalL = buffer.getSample(0, sample);
//        std::cout << "signalR voor = " << signalR << std::endl;
        float filterSignalL = bandpass175->processL(signalL);
        float filterSignalR = bandpass175->processR(signalL);
        float filterSignal1L = bandpass220->processL(signalR);
        float filterSignal1R = bandpass220->processR(signalR);
//        std::cout << "signalR na = " << filterSignalR << std::endl;
        
//        float filterSignal1L = bandpass1L.process(signalL);
//        float filterSignal1R = bandpass1R.process(signalR);
        
//        channelDataL[sample] = filterSignalL + filterSignal1L;
//        channelDataR[sample] = filterSignalR + filterSignal1R ;
        
        channelDataL[sample] = filterSignalL;
        channelDataR[sample] = filterSignalR;

        
        }
    
    
    
    
    
    
    
    
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        float* channelData = buffer.getWritePointer (channel);
//
//        // ..do something to the data...
//    }
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
