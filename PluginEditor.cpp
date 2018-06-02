/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
GuitarSynth_2AudioProcessorEditor::GuitarSynth_2AudioProcessorEditor (GuitarSynth_2AudioProcessor& p)
: AudioProcessorEditor (&p), processor (p),
rightPanel (Colours::darkgrey), leftPanel (Colours::darkgrey), bottomPanel(p, Colours::dimgrey)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible (rightPanel);
    addAndMakeVisible (leftPanel);
    addAndMakeVisible (mainPanelUp);
    addAndMakeVisible (bottomPanel);
    
    setSize (width, height);
}

GuitarSynth_2AudioProcessorEditor::~GuitarSynth_2AudioProcessorEditor()
{
}

//==============================================================================
void GuitarSynth_2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    getLookAndFeel().setColour (Slider::thumbColourId, Colours::rosybrown);
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void GuitarSynth_2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();
    
    auto panelWidth = bounds.getWidth() / 4;
    
    leftPanel.setBounds  (bounds.removeFromLeft  (panelWidth / 1.5));
    rightPanel.setBounds (bounds.removeFromRight (panelWidth / 1.2));
    mainPanelUp.setBounds (bounds.removeFromTop(bounds.getHeight()/2));
    bottomPanel.setBounds (bounds);
}
