/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include <iomanip>

//==============================================================================
// This is a handy slider subclass that controls an AudioProcessorParameter
// (may move this class into the library itself at some point in the future..)
class GuitarSynth_2AudioProcessorEditor::ParameterSlider   : public Slider,
private Timer
{
public:
    ParameterSlider (AudioProcessorParameter& p)
    : Slider (p.getName (256)), param (p)
    {
        startTimerHz (30);
        updateSliderPos();
    }
    
    void valueChanged() override        { param.setValueNotifyingHost ((float) Slider::getValue()); }
    
    void timerCallback() override       { updateSliderPos(); }
    
    void startedDragging() override     { param.beginChangeGesture(); }
    void stoppedDragging() override     { param.endChangeGesture();   }
    
    double getValueFromText (const String& text) override   { return param.getValueForText (text); }
    String getTextFromValue (double value) override         { return param.getText ((float) value, 1024); }
    
    void updateSliderPos()
    {
        const float newValue = param.getValue();
        
        if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
            Slider::setValue (newValue, NotificationType::dontSendNotification);
    }
    
    AudioProcessorParameter& param;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterSlider)
};

//==============================================================================
GuitarSynth_2AudioProcessorEditor::GuitarSynth_2AudioProcessorEditor (GuitarSynth_2AudioProcessor& owner)
: AudioProcessorEditor (owner), processor (owner),
timecodeDisplayLabel (String()),
LFOglideLabel(String(), "LFO GLIDE"),
frequencyLabel (String(), "FREQUENCY"),
amplitudeLabel (String(), "DRY/WET"),
LFOfrequencyLabel (String(), "LFO FREQUENCY"),
LFOdepthLabel (String(), "LFO DEPTH"),
waveFormLabel (String(), "LFO WAVEFORM"),
fmRatioLabel (String(), "FM RATIO"),
fmModDepthLabel (String(), "FM MOD DEPTH"),
driveLabel (String(), "DRIVE"),
rangeLabel (String(), "RANGE"),
attackReleaseLabel (String(), "ATTACK-RELEASE"),
tuneLabel (String(), "TUNNING"),
portamentoLabel (String(), "PORTAMENTO")
{
    // add some sliders..
    
    float fontsize = 15.0f;
    
    addAndMakeVisible (waveFormBox);
    
    auto i = 1;
    for (auto choice : processor.waveFormParam->choices)
        waveFormBox.addItem (choice, i++);
    
    waveFormBox.addListener (this);
    waveFormBox.setSelectedId (processor.waveFormParam->getIndex() + 1);
    
    addAndMakeVisible (glideSlider = new ParameterSlider (*owner.glideParam));
    glideSlider-> setRange (0.0, 1.0, 0.0);
    glideSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    
    
    addAndMakeVisible (knobs.add (driveSlider = new ParameterSlider (*owner.driveParam)));
    driveSlider->setSliderStyle (Slider::Rotary);
    driveSlider-> setRange (0.0, 1.0, 0.0);
    driveSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
   
    
    addAndMakeVisible (knobs.add (rangeSlider = new ParameterSlider (*owner.rangeParam)));
    rangeSlider->setSliderStyle (Slider::Rotary);
    rangeSlider-> setRange (0.0, 1.0, 0.0);
    rangeSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    
    addAndMakeVisible (knobs.add (fmRatioSlider = new ParameterSlider (*owner.fmRatioParam)));
    fmRatioSlider->setSliderStyle (Slider::Rotary);
    fmRatioSlider-> setRange (0.0, 1.0, 0.0);
    fmRatioSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    
    addAndMakeVisible (knobs.add (fmModDepthSlider = new ParameterSlider (*owner.fmModDepthParam)));
    fmModDepthSlider->setSliderStyle (Slider::Rotary);
    fmModDepthSlider-> setRange (0.0, 1.0, 0.0);
    fmModDepthSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
//    fmModDepthSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    
    
    addAndMakeVisible (knobs.add (LFOfrequencySlider = new ParameterSlider (*owner.LFOfrequencyParam)));
    LFOfrequencySlider->setSliderStyle (Slider::Rotary);
    LFOfrequencySlider-> setRange (0.0, 1.0, 0.0);
    LFOfrequencySlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    
    addAndMakeVisible (knobs.add (LFOdepthSlider = new ParameterSlider (*owner.LFOdepthParam)));
    LFOdepthSlider->setSliderStyle (Slider::Rotary);
    LFOdepthSlider-> setRange (0.0, 1.0, 0.0);
    LFOdepthSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    
    addAndMakeVisible (knobs.add (attackReleaseSlider = new ParameterSlider (*owner.attackReleaseParam)));
    attackReleaseSlider->setSliderStyle (Slider::Rotary);
    attackReleaseSlider-> setRange (0.0, 1.0, 0.0);
    attackReleaseSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    
    addAndMakeVisible (knobs.add (tuneSlider = new ParameterSlider (*owner.tuneParam)));
    tuneSlider->setSliderStyle (Slider::Rotary);
    tuneSlider-> setRange (0.0, 1.0, 0.0);
    tuneSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    
    addAndMakeVisible (knobs.add (portamentoSlider = new ParameterSlider (*owner.portamentoParam)));
    portamentoSlider->setSliderStyle (Slider::LinearVertical);
    portamentoSlider-> setRange (0.0, 1.0, 0.0);
    portamentoSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
    
    //ad Labels to the sliders
    tuneLabel.attachToComponent(tuneSlider, false);
    tuneLabel.setJustificationType (Justification::centredTop);
    tuneLabel.setFont (Font (fontsize));
    
    portamentoLabel.attachToComponent (portamentoSlider, false);
    portamentoLabel.setJustificationType (Justification::centredTop);
    portamentoLabel.setFont (Font (fontsize));
    
    fmRatioLabel.attachToComponent (fmRatioSlider, false);
    fmRatioLabel.setJustificationType (Justification::centredTop);
    fmRatioLabel.setFont (Font (fontsize));
    
    driveLabel.attachToComponent (driveSlider, false);
    driveLabel.setJustificationType (Justification::centredTop);
    driveLabel.setFont (Font (fontsize));
    
    rangeLabel.attachToComponent (rangeSlider, false);
    rangeLabel.setJustificationType (Justification::centredTop);
    rangeLabel.setFont (Font (fontsize));

    fmModDepthLabel.attachToComponent (fmModDepthSlider, false);
    fmModDepthLabel.setJustificationType (Justification::centredTop);
    fmModDepthLabel.setFont (Font (fontsize));
    
    attackReleaseLabel.attachToComponent (attackReleaseSlider, false);
    attackReleaseLabel.setJustificationType (Justification::centredTop);
    attackReleaseLabel.setFont (Font (fontsize));
    
    LFOfrequencyLabel.attachToComponent (LFOfrequencySlider, false);
    LFOfrequencyLabel.setJustificationType (Justification::centredTop);
    LFOfrequencyLabel.setFont (Font (fontsize));
    
    LFOdepthLabel.attachToComponent (LFOdepthSlider, false);
    LFOdepthLabel.setJustificationType (Justification::centredTop);
    LFOdepthLabel.setFont (Font (fontsize));
    
    addAndMakeVisible (waveFormLabel);
    waveFormLabel.setJustificationType (Justification::centredLeft);
    waveFormLabel.attachToComponent (&waveFormBox, true);
    
    addAndMakeVisible (LFOglideLabel);
    LFOglideLabel.setJustificationType (Justification::centredLeft);
    LFOglideLabel.attachToComponent (glideSlider, true);
    

    
    // set resize limits for this plug-in
    setResizeLimits (1000, 250, 1000, 250);
    
    // set our component's initial size to be the last one that was stored in the filter's settings
    setSize (owner.lastUIWidth,
             owner.lastUIHeight);
    
    updateTrackProperties();
    
    // start a timer which will keep our timecode display updated
    startTimerHz (30);
}

GuitarSynth_2AudioProcessorEditor::~GuitarSynth_2AudioProcessorEditor()
{
}

//==============================================================================
void GuitarSynth_2AudioProcessorEditor::paint (Graphics& g)
{
    getLookAndFeel().setDefaultSansSerifTypefaceName("phosphate");
    g.setColour(Colours::darkgrey);
    g.fillAll();
    
    auto rect = getLocalBounds();
    g.setColour(Colours::dimgrey);
    g.drawLine(0, 54, getWidth(), 54, 20);
    
    do {
        for(int i = 0; i < 9; i++){
             g.drawLine(getWidth()/9 * i, getHeight()-200, getWidth()/9 * i , getHeight(), 20);
            i += 1;
        }
    }while (false);
    g.drawLine(getWidth(), getHeight()-200, getWidth(), getHeight(), 20);
    
    g.drawLine(0, 250, getWidth(), 250 , 100);



    
    g.setColour(Colours::white);
    
    getLookAndFeel().setColour (Slider::thumbColourId, Colours::rosybrown);
    
    
    g.setFont(11.0f);
    g.setColour(Colours::white);
    
    
 
    
}

void GuitarSynth_2AudioProcessorEditor::resized()
{
    getProcessor().lastUIWidth = getWidth();
    getProcessor().lastUIHeight = getHeight();
    
    //get a rectangle with local bounds, then scale the objects in that rectangle
    auto r = getLocalBounds();
    r.removeFromLeft(10);
    
    //reser some space for top section
    auto topSection = r.removeFromTop(30);
    //top section objects
    waveFormBox.setBounds(100,15,200,20);
    glideSlider->setBounds(450, 0, 200, 50);
    
    r.removeFromTop (20);
    auto sliderArea = (r.removeFromTop (35));
    
    //divide knobs evenly over the with of the plugin screen
    auto bounds = getLocalBounds();
    auto knobSize = bounds.getWidth() / knobs.size();

    for (int i = 0; i < knobs.size(); ++i)
    {
        knobs[i]->setBounds (knobSize * (i % knobs.size()),
                                 bounds.getHeight()/3,
                                 knobSize,
                                 knobSize);
    }

}

//==============================================================================
void GuitarSynth_2AudioProcessorEditor::timerCallback()
{
    
}

void GuitarSynth_2AudioProcessorEditor::hostMIDIControllerIsAvailable (bool controllerIsAvailable)
{
    
}

void GuitarSynth_2AudioProcessorEditor::updateTrackProperties ()
{
    auto trackColour = getProcessor().trackProperties.colour;
    auto& lf = getLookAndFeel();
    
    backgroundColour = (trackColour == Colour() ? lf.findColour (ResizableWindow::backgroundColourId)
                        : trackColour.withAlpha (1.0f).withBrightness (0.266f));
    repaint();
}

//==============================================================================

void GuitarSynth_2AudioProcessorEditor::comboBoxChanged (ComboBox* box)
{
    auto index = box->getSelectedItemIndex();
    
    if (box == &waveFormBox)
    {
        processor.waveFormParam->operator= (index);
    }
}

