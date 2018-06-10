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
    
    lastPosInfo.resetToDefault();
    addParameter (driveParam = new AudioParameterFloat ("DRIVE",  "DRIVE", 0.1f, 10.f, 0.1f));
    addParameter (rangeParam = new AudioParameterFloat ("RANGE",  "RANGE", 0.1f, 10.f, 0.1f));
    addParameter (fmRatioParam = new AudioParameterFloat ("FM_RATIO",  "FM_RATIO", 0.1f, 10.f, 0.1f));
    addParameter (fmModDepthParam = new AudioParameterFloat ("FM_MOD_DEPTH",  "FM_MOD_DEPTH", 0.1f, 10.f, 0.1f));
    addParameter (glideParam = new AudioParameterFloat ("GLIDE",  "LFO_glide", 0.1f, 10.f, 0.1f));
    addParameter (attackReleaseParam  = new AudioParameterFloat ("ATTACK_RELEASE",  "ATTACK_RELEASE", 0.0f, 1200.0f, 0.9f));
    addParameter (LFOfrequencyParam  = new AudioParameterFloat ("LFO_Frequency",  "LFO_Frequency", -10.0f, 10.0f,0.0f));
    addParameter (LFOdepthParam = new AudioParameterFloat ("LFO_depth", "LFO_depth", 0.0f, 100.0f, 0.5f));
    addParameter (waveFormParam   = new AudioParameterChoice ("Wave_form", "LFO_wave form", { "rising saw", "falling saw", "sine", "square", "noise generator" }, 4));
    addParameter (amplitudeParam = new AudioParameterFloat ("Dry_Wet", "Dry_Wet", 0.0f, 1.0f, 0.5f));
    
    
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
//    oscillators = new Oscillator*[3];
    
    //add oscillators
//    oscillators[0] = new SineWave(lastSampleRate, 220, 0);
//    oscillators[1] = new NoiseOscillator();
//    oscillators[2] = new SineWave(lastSampleRate, 0, 0);
    
    synth = new Synth(lastSampleRate);
    
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


            //zerox analysis, checks how many times the signal crosses the zero line.
            zerox.calculate(signal);
            //depending on the amount of crossings, the synthsample changes from a harmonic to a disharmonic sound(noise)
            int oscIndex = zerox.getZerox() - 1;
//            double synthSample = oscillators[oscIndex]->getSample();
//            synthSample = oscillators[0]->getSample();
            synthSample = synth->process();
//            synthSample = applyDistortion(synthSample);

            setBPM(lastPosInfo);
            setFrequency();
            synth->setLFO(*waveFormParam);
            updateCurrentTimeInfoFromHost();
            updateSynth();
            
//            //sets phase one tick forward
//            oscillators[0]->tick();
//            oscillators[1]->tick();
//            oscillators[2]->tick();
            
            //update frequency for fm-synthesis
//            updateFrequency();
            
            //Synthsignal gets filtered and is multiplied with envelope follower values that where calculated earlier
            for (int filterIndex = 30; filterIndex < 45; filterIndex++){
                float filterSignal = bandPassFilters[filterIndex]->process(channel, synthSample);
                addedfilterSignal1 = filterSignal * ( envFollowValues[filterIndex-30]) + addedfilterSignal1;
            }


            //apply distortion effect
//            addedfilterSignal1 = applyDistortion(addedfilterSignal1);
            
            //send data to correct channel
            channelData[sample] = addedfilterSignal1 + ( envFollowValues[10] * applyDistortion(synthSample));
            addedfilterSignal1 = 0;
            addedfilterSignal2 = 0;
        }
    }
}

void GuitarSynth_2AudioProcessor::updateSynth()
{
    synth->setRatio(*fmRatioParam);
    synth->setModDepth(*fmModDepthParam);
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
        
        int detectSize = 200;
        
        for (int i = 0; i <detectSize; i++){
            
            lowPassPitch = lowPass->process(pitchdetected);
        }

        for (int i = 0; i <detectSize; i++){
            detectedPitches[i] = pitchdetected;
        }
        
        //look for number that appears the most in the array of detected pitches
        int max_count = 0;
        
        for (int i=0;i<detectSize;i++)
        {
            int count=1;
            for (int j=i+1;j<detectSize;j++)
                if (detectedPitches[i]==detectedPitches[j])
                    count++;
            if (count>max_count)
                max_count = count;
        }
        
        for (int i=0;i<detectSize;i++)
        {
            int count=1;
            for (int j=i+1;j<detectSize;j++)
                if (detectedPitches[i]==detectedPitches[j])
                    count++;
            if (count==max_count)
                mostDetected = detectedPitches[i];
        }
        
        fmFrequency = (round(12*log2( mostDetected / 440 ) + 69));
        
        synthFrequency = synth->mtof(fmFrequency);
//        std::cout << "frecuency = " << synthFrequency << std::endl;
        addedFreqs = 0;
    }

}


double GuitarSynth_2AudioProcessor::applyDistortion(double signal)
{
    drive = *driveParam;
    range = *rangeParam;
    signalDistortion = signal * drive *  range;
    signalDistortion *= (2.f / float_Pi) * atan(signalDistortion);
//    signalDistortion =  signalDistortion * blend;
//    signal = signal * ((blend * -1) + 1);
    
    return signal + signalDistortion;
}

void GuitarSynth_2AudioProcessor::updateCurrentTimeInfoFromHost()
{
    if (AudioPlayHead* ph = getPlayHead())
    {
        AudioPlayHead::CurrentPositionInfo newTime;
        
        if (ph->getCurrentPosition (newTime))
        {
            lastPosInfo = newTime;
            return;
        }
    }
    
    lastPosInfo.resetToDefault();
}


void GuitarSynth_2AudioProcessor::setBPM(AudioPlayHead::CurrentPositionInfo bpm)
{
    beats = bpm.bpm;
    
    if(bpm.isLooping && (bpm.isPlaying || bpm.isRecording)){
        if(!startTimeSet){
            startLoop = bpm.timeInSeconds;
            startTimeSet = true;
        }
        if(bpm.timeInSeconds == startLoop)
            setOSCphase(bpm);
    }
    
    if (bpm.isPlaying){
        if(!setPhase){
            setPhase = true;
            setOSCphase(bpm);
        }
    }
    else if (!bpm.isPlaying && !bpm.isRecording){
        setPhase = false;
        startTimeSet = false;
    }
    
    
}



void GuitarSynth_2AudioProcessor::setFrequency()
{
    glide = *glideParam * -1 + 10.1;
    (glide < 10) ? LFO = lowPass->process(synth->getLFOsample()* *LFOdepthParam) : LFO = synth->getLFOsample()* *LFOdepthParam;
    lowPass->setFc(glide/sampleRate);
    
    synth->setFrequency(synthFrequency + LFO);
    
    
    if(*LFOfrequencyParam < 0){
        LFOP = *LFOfrequencyParam - 1;
        LFOI = int(*LFOfrequencyParam);
        LFOf = rateValues[(LFOI * -1)];
        syncfreq = beats/LFOf;
        synth->setLFOfreq(syncfreq);
        
        if(LFOI != previousLFOfreq){
            if(!setPhaseSwitch){
                setPhaseSwitch = true;
                setOSCphase(lastPosInfo);
            }
            else{
                
                previousLFOfreq = LFOI;
                setPhaseSwitch = false;
            }
        }
        else {
            previousLFOfreq = LFOI;
        }
    }else{
        if(*LFOfrequencyParam < 0 && *LFOfrequencyParam > -0.5){ oscillators[1]->setFrequency(0); }
        else{
            synth->setLFOfreq(*LFOfrequencyParam);
        }
    }
}

void GuitarSynth_2AudioProcessor::setOSCphase(AudioPlayHead::CurrentPositionInfo bpm)
{
    double beatss = bpm.bpm;
    double phaseLenght = 60 / beatss;
    double timer = fmod(bpm.timeInSeconds,phaseLenght)/phaseLenght;
    synth->setPhaseLFO(timer);
}
//==============================================================================

//store parameters in the memory block.
void GuitarSynth_2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    
    // Create an outer XML element..
    XmlElement xml ("RMSETTINGS");
    
    // add some attributes to it..
    xml.setAttribute ("uiWidth", lastUIWidth);
    xml.setAttribute ("uiHeight", lastUIHeight);
    
    // Store the values of all our parameters, using their param ID as the XML attribute
    for (auto* param : getParameters()){
        if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param)){
            xml.setAttribute (p->paramID, p->getValue());
        }
    }
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}


// restore the parameters from this memory block
void GuitarSynth_2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("RMSETTINGS"))
        {
            // ok, now pull out our last window size..
            lastUIWidth  = jmax (xmlState->getIntAttribute ("uiWidth", lastUIWidth), 400);
            lastUIHeight = jmax (xmlState->getIntAttribute ("uiHeight", lastUIHeight), 200);
            
            // Now reload our parameters..
            for (auto* param : getParameters())
                if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
                    p->setValue ((float) xmlState->getDoubleAttribute (p->paramID, p->getValue()));
        }
    }
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GuitarSynth_2AudioProcessor();
}
