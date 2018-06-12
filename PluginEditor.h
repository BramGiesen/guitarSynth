/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include <iostream>


//==============================================================================
class GuitarSynth_2AudioProcessorEditor  : public AudioProcessorEditor,
private Timer, private ComboBox::Listener
{
public:
    GuitarSynth_2AudioProcessorEditor (GuitarSynth_2AudioProcessor&);
    ~GuitarSynth_2AudioProcessorEditor();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void hostMIDIControllerIsAvailable (bool) override;
    void updateTrackProperties();
    
private:
    void comboBoxChanged (ComboBox*) override;
    void setBPM(AudioPlayHead::CurrentPositionInfo);
    class ParameterSlider;
    
    int drawLine = 0;
    double beats = 0;
    
    GuitarSynth_2AudioProcessor& processor;
    
    //Labels
    Label timecodeDisplayLabel, LFOglideLabel, frequencyLabel, amplitudeLabel, LFOfrequencyLabel, LFOdepthLabel, waveFormLabel, fmRatioLabel, fmModDepthLabel, driveLabel, rangeLabel, attackReleaseLabel, tuneLabel, portamentoLabel;
    
    //Sliders
    ScopedPointer<ParameterSlider> glideSlider, frequencySlider, amplitudeSlider, LFOfrequencySlider, LFOdepthSlider, fmRatioSlider, fmModDepthSlider, driveSlider, rangeSlider, attackReleaseSlider, tuneSlider, portamentoSlider;
    
    //arrays to put the sliders and knobs in
    OwnedArray<Slider> knobs;
    OwnedArray<Label> labels;
    
    ComboBox waveFormBox;
    Colour backgroundColour;
    
    //values to print for LFO, the numbers represent beats
    std::string rateValues[11]{"32","32t","16","16t","8","8t","4","4t","2","2t","1"};
    std::string LFOf;
    //==============================================================================
    GuitarSynth_2AudioProcessor& getProcessor() const
    {
        return static_cast<GuitarSynth_2AudioProcessor&> (processor);
    }
    
};


