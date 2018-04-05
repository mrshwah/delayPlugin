/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DelayPlugInAudioProcessorEditor::DelayPlugInAudioProcessorEditor (DelayPlugInAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 600);
    
    delaySlider.addListener(this);
    delaySlider.setBounds(0,0,150,150);
    delaySlider.setCentrePosition(100, 150);
    delaySlider.setSliderStyle(Slider::RotaryVerticalDrag);
    delaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    delaySlider.setRange(0, 1000, 1);
    delaySlider.setValue(1000);
    addAndMakeVisible(delaySlider);
    
    delayLabel.setFont(Font::Font("Avenir Next", 16.0f, 1));
    delayLabel.setBounds(70, 125, 60, 16);
    delayLabel.setText("TIME MS", dontSendNotification);
    addAndMakeVisible(delayLabel);
    
    feedbackSlider.addListener(this);
    feedbackSlider.setBounds(0,0,150,150);
    feedbackSlider.setCentrePosition(300, 150);
    feedbackSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    feedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    feedbackSlider.setRange(0, 99, 1);
    addAndMakeVisible(feedbackSlider);
    
    feedbackLabel.setFont(Font::Font("Avenir Next", 16.0f, 1));
    feedbackLabel.setBounds(260, 125, 80, 16);
    feedbackLabel.setText("FEEDBACK %", dontSendNotification);
    addAndMakeVisible(feedbackLabel);
    
    highPassSlider.addListener(this);
    highPassSlider.setBounds(0,0,150,150);
    highPassSlider.setCentrePosition(100, 450);
    highPassSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    highPassSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    highPassSlider.setRange(0, 1000, 1);
    addAndMakeVisible(highPassSlider);
    
    highPassLabel.setFont(Font::Font("Avenir Next", 16.0f, 1));
    highPassLabel.setBounds(75, 425, 60, 16);
    highPassLabel.setText("HPF HZ", dontSendNotification);
    addAndMakeVisible(highPassLabel);
    
    lowPassSlider.addListener(this);
    lowPassSlider.setBounds(0,0,150,150);
    lowPassSlider.setCentrePosition(300, 450);
    lowPassSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    lowPassSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    lowPassSlider.setRange(2000, 20000, 1);
    lowPassSlider.setValue(20000);
    addAndMakeVisible(lowPassSlider);
    
    lowPassLabel.setFont(Font::Font("Avenir Next", 16.0f, 1));
    lowPassLabel.setBounds(275, 425, 60, 16);
    lowPassLabel.setText("LPF HZ", dontSendNotification);
    addAndMakeVisible(lowPassLabel);
    
    wetDrySlider.addListener(this);
    wetDrySlider.setBounds(0,0,150,150);
    wetDrySlider.setCentrePosition(500, 300);
    wetDrySlider.setSliderStyle(Slider::RotaryVerticalDrag);
    wetDrySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    wetDrySlider.setRange(0, 100, 1);
    wetDrySlider.setValue(50);
    addAndMakeVisible(wetDrySlider);
    
    wetDryLabel.setFont(Font::Font("Avenir Next", 16.0f, 1));
    wetDryLabel.setBounds(460, 275, 80, 16);
    wetDryLabel.setText("WET/DRY %", dontSendNotification);
    addAndMakeVisible(wetDryLabel);
}

DelayPlugInAudioProcessorEditor::~DelayPlugInAudioProcessorEditor()
{
}

//==============================================================================
void DelayPlugInAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont(Font::Font("Avenir Next", 36.0f, 0));
    g.drawFittedText("DELAY", 0, 50, 400, 36, Justification::centred, 1);
    g.drawFittedText("FILTERS", 0, 350, 400, 36, Justification::centred, 1);
    g.drawFittedText("OUTPUT", 400, 200, 200, 36, Justification::centred, 1);
}

void DelayPlugInAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void DelayPlugInAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &delaySlider) {
        processor.delay = delaySlider.getValue() / 1000;
    }
    else if (slider == &feedbackSlider)
        processor.feedback = .01 * feedbackSlider.getValue();
    else if (slider == &wetDrySlider) {
        processor.wetMix = wetDrySlider.getValue() / 100;
    }
}
