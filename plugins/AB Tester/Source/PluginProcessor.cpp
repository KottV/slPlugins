/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <random>

using namespace gin;

//==============================================================================
String abTextFunction (const Parameter&, float v)
{
    return v > 0.0f ? "A" : "B";
}

//==============================================================================
ABTesterAudioProcessor::ABTesterAudioProcessor()
{
    //==============================================================================
    addPluginParameter (new Parameter (PARAM_AB,    "A / B",        "", "",     0.0f,     1.0f, 1.0f,    0.0f, 1.0f, abTextFunction));
    addPluginParameter (new Parameter (PARAM_LEVEL, "Level",      "", "dB",  -100.0f,     6.0f, 0.0f,    0.0f, 5.f));
}

ABTesterAudioProcessor::~ABTesterAudioProcessor()
{
}

//==============================================================================
void ABTesterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    aVal.reset (sampleRate, 0.05);
    bVal.reset (sampleRate, 0.05);
}

void ABTesterAudioProcessor::releaseResources()
{
}

void ABTesterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer&)
{
    aVal.setValue (parameterIntValue (PARAM_AB) == 0 ? Decibels::decibelsToGain (parameterValue (PARAM_LEVEL)) : 0);
    bVal.setValue (parameterIntValue (PARAM_AB) == 1 ? Decibels::decibelsToGain (parameterValue (PARAM_LEVEL)) : 0);

    const int numSamples = buffer.getNumSamples();
    
    float* aL = buffer.getWritePointer (0);
    float* aR = buffer.getWritePointer (1);
    float* bL = buffer.getWritePointer (2);
    float* bR = buffer.getWritePointer (3);

    // Apply A gain
    for (int s = 0; s < numSamples; s++)
    {
        float g = aVal.getNextValue();
        aL[s] *= g;
        aR[s] *= g;
    }
    // Apply B gain
    for (int s = 0; s < numSamples; s++)
    {
        float g = bVal.getNextValue();
        aL[s] += bL[s] * g;
        aR[s] += bR[s] * g;
    }
}

//==============================================================================
bool ABTesterAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* ABTesterAudioProcessor::createEditor()
{
    editor = new ABTesterAudioProcessorEditor (*this);
    return editor;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ABTesterAudioProcessor();
}