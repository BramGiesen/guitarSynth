/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include <thread>

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "/Users/BramGiesen/Documents/HKU/aubio-0.4.5.darwin_framework/aubio.framework/Headers/aubio.h"

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
    
    
    //clean up aubio
    del_aubio_pitch (o);
    del_fvec (out);
//    del_fvec (input);
    aubio_cleanup ();
    
    if(pitchDetectThread.joinable()) pitchDetectThread.join();
    delete oscillators;
    oscillators = nullptr;
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
    
    //create a list for the oscillators
    oscillators = new Oscillator*[3];
    
    //add oscillators
    oscillators[0] = new SineWave(lastSampleRate, 220, 0);
    oscillators[1] = new NoiseOscillator();
    oscillators[2] = new SineWave(lastSampleRate, 0, 0);
    
    //create a list of biquad objects
    int numberOfBiquads = 60;
    bandPassFilters = new Biquad*[numberOfBiquads];
    
    //create 60 bandpasses 4 * 15 different frequency's
    for (int i = 0; i < numberOfBiquads; i++){
        bandPassFilters[i] = new Biquad(1.0, filterFreqs[i % 15] / lastSampleRate, 46.0);
    }
    
    //list for the envelope follower objects
    envelopeFollowers = new EnvelopeFollower*[15];
    
    //create 15 envelope followers
    for (int i = 0; i < 15; i++){
        envelopeFollowers[i] = new EnvelopeFollower;
    }
    
    //start aubio pitch detection thread
    StartThread();

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

//audio process function
void GuitarSynth_2AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    //to prevent screaming feedback if the chanels aren't clean
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // get numsamples
    for(int sample = 0; sample < buffer.getNumSamples(); ++sample){
    
    //load samples in buffer that is linked to aubio buffer
    audioBufferPitch[x++ % lenghtOfAudioBuffer] = buffer.getSample(0, sample);
       
        for (int channel = 0; channel< totalNumInputChannels; ++channel)
        {
            //get pointer to write data to the correct channel
            auto channelData = buffer.getWritePointer (channel);
            
            //get sample from JUCE buffer
            float  signal = buffer.getSample(channel, sample);
            
            //filter the signal with 15 bandpass filters.
            for (int filterIndex = 0; filterIndex < 15; filterIndex++){
                filterSignal1 = bandPassFilters[filterIndex]->process(channel, signal);
                envFollowValues[filterIndex] = envelopeFollowers[filterIndex]->process(filterSignal1);
            }

            //filter signal again and send filtered signal to envelope follower
//            for (int filterIndex = 15; filterIndex < 30; filterIndex++){
//                filterSignal2 = bandPassFilters[filterIndex]->process(channel, filterSignal1);
                //process envolope followers and put the return values in a vector
//                envFollowValues[filterIndex-15] = envelopeFollowers[filterIndex-15]->process(filterSignal1);
//            }

            //zerox analysis, checks how many times the signal crosses the zero line.
            zerox.calculate(signal);
            //depending on the amount of crossings, the synthsample changes from a harmonic to a disharmonic sound(noise)
            int oscIndex = zerox.getZerox() - 1;
//            double synthSample = oscillators[oscIndex]->getSample();
            synthSample = oscillators[0]->getSample();

            
            //sets phase one tick forward
            oscillators[0]->tick();
            oscillators[1]->tick();
            oscillators[2]->tick();
            updateFrequency();
            
            //Synthsignal gets filtered and is multiplied with envelope follower values that where calculated earlier
            for (int filterIndex = 30; filterIndex < 45; filterIndex++){
                float filterSignal = bandPassFilters[filterIndex]->process(channel, synthSample);
                addedfilterSignal1 = filterSignal * (100 * envFollowValues[filterIndex-30]) + addedfilterSignal1;
            }

//            //filter the signal one last time
//            for (int filterIndex = 45; filterIndex < 60; filterIndex++){
//                float filterSignal = bandPassFilters[filterIndex]->process(channel, filterSignal1);
//                addedfilterSignal2 = (filterSignal * (100 * envFollowValues[filterIndex-45])) + addedfilterSignal2;
//            }
//
            
    
            //sends the filtered synth signal to the correct channel
            channelData[sample] = addedfilterSignal1;
            addedfilterSignal1 = 0;
            addedfilterSignal2 = 0;
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
//      exectute pitch detection
        aubio_pitch_do (o, input, out);
        
//      do something with output candidates
        smpl_t pitchdetected = fvec_get_sample(out, 0);
        
        
        for (int i = 0; i <200000; i++){
            
            lowPassPitch = lowPass->process(pitchdetected);
            addedFreqs = lowPassPitch + addedFreqs;
        }
        
        addedFreqs =  addedFreqs / 200000;
        
        fmFrequency = (round(12*log2( addedFreqs / 440 ) + 69));

        
        fmFrequency = mtof(fmFrequency);
        
//        if(fmFrequency < 130 && !init){
//            previousFrequency = fmFrequency;
//            init = true;
//        }

        if(fmFrequency != previousFrequency){
            //update frequency for fm-synthesis
            if((fmFrequency < (previousFrequency / 2)) || (fmFrequency > (previousFrequency * 2))){
                fmFrequency = previousFrequency;
            }
            if(fmFrequency < 50){
                fmFrequency = previousFrequency;
            }
//            oscillators[0]->setFrequency(fmFrequency);
            oscillatorFreq = fmFrequency;
            previousFrequency = fmFrequency;
        }

        addedFreqs = 0;
    }

}

void GuitarSynth_2AudioProcessor::updateFrequency()
{   //fm synthesis, 0 is the carrier 2 is the modulator
//    std::cout << "fmfreq = " << fmFrequency << std::endl;
    oscillators[2]->setFrequency(oscillatorFreq * ratio);
    oscillators[0]->setFrequency(oscillatorFreq + ((oscillators[2]->getSample())* (modDepth * oscillatorFreq * ratio)));
}

float GuitarSynth_2AudioProcessor::mtof(float aubioFreq)
{
    return pow(2.0,(aubioFreq-69.0)/12.0) * 440.0;
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
