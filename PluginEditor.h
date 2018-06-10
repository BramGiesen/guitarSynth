/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class GuitarSynth_2AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    GuitarSynth_2AudioProcessorEditor (GuitarSynth_2AudioProcessor&);
    ~GuitarSynth_2AudioProcessorEditor();

//==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    GuitarSynth_2AudioProcessor& processor;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    float a = 100;
    float height = a * 3;
    float width = a * 8;
    
    
//========================================================================================================
    
    struct RightSidePanel    : public Component
    {
        RightSidePanel (Colour c) : backgroundColour (c)
        {
           
            
            for (auto i = 0; i < 1; ++i)
                addAndMakeVisible (labelsRight.add (new Label({}, labelText[i])));
            
            for (int i = 0; i < 1; ++i)
            {
                auto* slider = new Slider();
                
                slider->setSliderStyle (Slider::SliderStyle::LinearVertical);
                slider->setTextBoxStyle (Slider::TextBoxBelow, true, 0, 0);
                labelsRight[i]->attachToComponent(slider, false);
                labelsRight[i]->setJustificationType(Justification::centred);
                addAndMakeVisible (knobsRight.add (slider));
            }
            
            
            
        }
        
        void paint (Graphics& g) override
        {
            g.fillAll (backgroundColour);
        }
        
        void resized() override
        {
            auto bounds = getLocalBounds();
            auto buttonSize = bounds.getWidth() / knobsRight.size();

            for (int i = 0; i < knobsRight.size(); ++i)
            {
                knobsRight[i]->setBounds (buttonSize * (i % knobsRight.size() ),
                                       buttonSize * bounds.getHeight() / 1000,
                                       buttonSize,
                                       bounds.getHeight()-60);
            }
        }
        
        Colour backgroundColour;
        std::string labelText[2]{"Attack-Release"};
        OwnedArray<Slider> knobsRight;
        OwnedArray<Label> labelsRight;
    };
 
    
    
//========================================================================================================
    
    
    
    
    struct LeftSidePanel    : public Component
    {
        LeftSidePanel (Colour c) : backgroundColour (c)
        {
            for (auto i = 0; i < 2; ++i)
                addAndMakeVisible (labelsLeft.add (new Label({}, textLabelLeft[i])));
            
            for (int i = 0; i < 2; ++i)
            {
                auto* slider = new Slider();
                
                slider->setSliderStyle (Slider::SliderStyle::LinearVertical);
                slider->setTextBoxStyle (Slider::TextBoxBelow, true, 0, 0);
                labelsLeft[i]->attachToComponent(slider, false);
                labelsLeft[i]->setJustificationType(Justification::centred);
                addAndMakeVisible (knobsLeft.add (slider));
            }
            
            
        }
        
        void paint (Graphics& g) override
        {
            g.fillAll (backgroundColour);
        }
        
        void resized() override
        {
            auto bounds = getLocalBounds();
            auto knobSize = bounds.getWidth() / 1.5;
            

            for (int i = 0; i < knobsLeft.size(); ++i)
            {
                knobsLeft[i]->setBounds (knobSize * (0.25),
                                     bounds.getHeight() / 2 * i + 20,
                                     knobSize,
                                     knobSize);
            }
        }
        
        Colour backgroundColour;
        std::string textLabelLeft[2]{"Input Volume", "Threshold"};
        OwnedArray<Slider> knobsLeft;
        OwnedArray<Label> labelsLeft;
        
    };
    
//========================================================================================================

    
    struct MainPanel    : public Component
    {
        MainPanel()
        {
            for (auto i = 0; i < 6; ++i)
                addAndMakeVisible (labelsMain.add (new Label({}, textLabelMain[i])));
            
            for (int i = 0; i < 6; ++i)
            {
                auto* slider = new Slider();
                slider->setSliderStyle (Slider::SliderStyle::Rotary);
                slider->setTextBoxStyle (Slider::NoTextBox, true, 0, 0);
                labelsMain[i]->attachToComponent(slider, false);
                labelsMain[i]->setJustificationType(Justification::centred);
                
                addAndMakeVisible (knobsMain.add (slider));
            }
        }
        
        void paint (Graphics& g) override
        {
            
            g.fillAll (Colours::grey);
            g.setColour(Colours::darkgrey);
            
            for(auto i = 0; i <4; i++)
                g.drawLine((getWidth()/3)*i, 0, (getWidth()/3)*i, getHeight(),5);
            
            for(auto i = 0; i <2; i++)
                g.drawLine(0, getHeight()*i, getWidth(), getHeight()*i,17);
           
        }
        
        void resized() override
        {
            auto bounds = getLocalBounds();
            auto knobSize = bounds.getWidth() / knobsMain.size();
            
            for (int i = 0; i < knobsMain.size(); ++i)
            {
                knobsMain[i]->setBounds (knobSize * (i % knobsMain.size()),
                                     bounds.getHeight() / 3,
                                     knobSize,
                                     knobSize);
            }
        }
        OwnedArray<Slider> knobsMain;
        OwnedArray<Label> labelsMain;
        std::string textLabelMain[6] { "Gain", "Tone", "Pulse Amp", "Pulse Width", "Cutoff", "Resonance"};
    };
    
    
//========================================================================================================
        
        struct BottomPanel   : public Component
        {
            BottomPanel (GuitarSynth_2AudioProcessor& p, Colour c) : processorRef(&p), backgroundColour (c)
            {
                
                for (auto i = 0; i < 3; ++i)
                    addAndMakeVisible (labelsBottom.add (new Label({}, textLabelBottom[i])));
                
                for(auto i = 0; i < 2; i++)
                {
                    auto* waveformChoice = new ComboBox();
                    addAndMakeVisible (choiceBottom.add (waveformChoice));
                    labelsBottom[1+i]->attachToComponent(waveformChoice, false);

                    auto &num = processorRef->waveFormParam->choices;
                    auto x = 1;
                    for (auto &choice : processorRef->waveFormParam->choices)
                        waveformChoice->addItem (choice, x++);
                }
                
                for (int i = 0; i < 2; ++i)
                {
                    auto* slider = new Slider();
                    slider->setSliderStyle (Slider::SliderStyle::Rotary);
                    slider->setTextBoxStyle (Slider::NoTextBox, true, 0, 0);
                    labelsBottom[i]->attachToComponent(slider, false);
                    labelsBottom[i]->setJustificationType(Justification::centred);
                    
                    addAndMakeVisible (knobsBottom.add (slider));
                }
                
            }
            
            void paint (Graphics& g) override
            {
                g.fillAll (backgroundColour);
                g.setColour(Colours::darkgrey);
                
                g.drawLine(0, getHeight(), getWidth(), getHeight(),17);
//                g.drawLine((getWidth()/2), 0, (getWidth()/2), getHeight(),5);
                
                for(auto i = 0; i <4; i++)
                    g.drawLine(getWidth()*i, 0, getWidth()*i, getHeight(),5);
            }
            
            void resized() override
            {
                auto bounds = getLocalBounds();
                bounds.removeFromLeft(int(bounds.getWidth()/2));
                bounds.removeFromRight(int(bounds.getWidth()/10));
                bounds.removeFromTop(int(bounds.getHeight()/5));
                bounds.removeFromBottom(int(bounds.getHeight()/1.8));
//                bounds.removeFromLeft(20);
                auto topHalf = bounds;
              
                choiceBottom[1]->setBounds(topHalf.removeFromTop(getHeight()/5));
//                choiceBottom[0]->setBounds(topHalf);
           
                auto knobSize = bounds.getWidth() / (knobsBottom.size());

                for (int i = 0; i < knobsBottom.size(); ++i)
                {
                    knobsBottom[i]->setBounds (knobSize * (i % knobsBottom.size()),
                                         bounds.getHeight() / 2,
                                         knobSize,
                                         knobSize);
                }
            }
            
            GuitarSynth_2AudioProcessor *processorRef;
            Colour backgroundColour;
            OwnedArray<Slider> knobsBottom;
            OwnedArray<ComboBox> choiceBottom;
            OwnedArray<Label> labelsBottom;
            std::string textLabelBottom[4] {"LFO Rate", "LFO Depth", "LFO Wave Form :"};
            std::string choices[4] {"sine", "Saw", "Square", "Pulse"};
        };
       
//        OwnedArray<Slider> sliders;
//    };
 //==================================================================================
    RightSidePanel rightPanel;
    LeftSidePanel leftPanel;
    MainPanel mainPanelUp;
    BottomPanel bottomPanel;
    
//===================================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuitarSynth_2AudioProcessorEditor)
};
