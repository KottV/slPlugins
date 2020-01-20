/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PitchTrackAudioProcessor::PitchTrackAudioProcessor()
{
}

PitchTrackAudioProcessor::~PitchTrackAudioProcessor()
{
}

//==============================================================================
void PitchTrackAudioProcessor::prepareToPlay (double sampleRate_, int samplesPerBlock)
{
    sampleRate = sampleRate_;
    
    scratch.setSize (1, samplesPerBlock);
}

void PitchTrackAudioProcessor::releaseResources()
{
}

void PitchTrackAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    outputLevel.trackBuffer (scratch);
}

//==============================================================================
bool PitchTrackAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* PitchTrackAudioProcessor::createEditor()
{
    return new PitchTrackAudioProcessorEditor (*this);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PitchTrackAudioProcessor();
}