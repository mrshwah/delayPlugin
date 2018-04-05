/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DelayPlugInAudioProcessor::DelayPlugInAudioProcessor()
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
}

DelayPlugInAudioProcessor::~DelayPlugInAudioProcessor()
{
    delay = 1000;
    delaySmooth = 0.0f;
    feedback = 0.0f;
    delayBufferSize = 1;
    delayReadPointer = 0;
    delayWritePointer = 0;
    wetMix = 0.5f;
}

//==============================================================================
const String DelayPlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DelayPlugInAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DelayPlugInAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DelayPlugInAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DelayPlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DelayPlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DelayPlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DelayPlugInAudioProcessor::setCurrentProgram (int index)
{
}

const String DelayPlugInAudioProcessor::getProgramName (int index)
{
    return {};
}

void DelayPlugInAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DelayPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    delayBufferSize = (int) (sampleRate);
    
    delayBuffer.setSize(getTotalNumInputChannels(), delayBufferSize);
    delayBuffer.clear();
}

void DelayPlugInAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DelayPlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DelayPlugInAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    int drp, dwp;
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelInput = buffer.getWritePointer(channel);
        float* delaySamples = delayBuffer.getWritePointer(channel);
        
        drp = delayReadPointer;
        dwp = delayWritePointer;
        
        for(int n = 0; n < buffer.getNumSamples(); ++n)
        {
            inSample = channelInput[n];
            outSample = 0.0f;

            delaySmooth = delay * 0.001 + delaySmooth*0.999;
            
            drp = (int) (dwp - (delaySmooth * getSampleRate()) + delayBufferSize) % delayBufferSize;
            
            outSample = (1 - wetMix) * inSample + wetMix * delaySamples[drp];
            
            delaySamples[dwp] = inSample + delaySamples[drp] * feedback;
            
            ++drp %= delayBufferSize;
            ++dwp %= delayBufferSize;
            
            channelInput[n] = outSample;
        }
    }
    
    delayReadPointer = drp;
    delayWritePointer = dwp;
}

//==============================================================================
bool DelayPlugInAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DelayPlugInAudioProcessor::createEditor()
{
    return new DelayPlugInAudioProcessorEditor (*this);
}

//==============================================================================
void DelayPlugInAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DelayPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DelayPlugInAudioProcessor();
}
