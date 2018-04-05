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
class DelayPlugInAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    DelayPlugInAudioProcessorEditor (DelayPlugInAudioProcessor&);
    ~DelayPlugInAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider *slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DelayPlugInAudioProcessor& processor;
    Slider delaySlider;
    Label delayLabel;
    Slider feedbackSlider;
    Label feedbackLabel;
    Slider highPassSlider;
    Label highPassLabel;
    Slider lowPassSlider;
    Label lowPassLabel;
    Slider wetDrySlider;
    Label wetDryLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayPlugInAudioProcessorEditor)
};
