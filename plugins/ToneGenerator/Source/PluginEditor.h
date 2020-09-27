/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class slToneAudioProcessorEditor  : public gin::ProcessorEditor
{
public:
    slToneAudioProcessorEditor (slToneAudioProcessor&);
    ~slToneAudioProcessorEditor() override;

    //==============================================================================
    void resized() override;

private:
    slToneAudioProcessor& toneProcessor;
    
    gin::TriggeredScope scope {toneProcessor.fifo};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (slToneAudioProcessorEditor)
};
