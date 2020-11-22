/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace gin;

//==============================================================================
LimiterAudioProcessorEditor::LimiterAudioProcessorEditor (LimiterAudioProcessor& p)
    : gin::ProcessorEditor (p, 60, 100), limProc (p)
{
    for (auto pp : p.getPluginParameters())
    {
        ParamComponent* pc;
        
        if (pp->isOnOff())
            pc = new Switch (pp);
        else
            pc = new Knob (pp);
        
        addAndMakeVisible (pc);
        controls.add (pc);
    }

    addAndMakeVisible (meter);
    addAndMakeVisible (inputMeter);
    addAndMakeVisible (outputMeter);
    addAndMakeVisible (reductionMeter);
    reductionMeter.setTopDown (true);

    addAndMakeVisible (scope);
    scope.setNumChannels (3);
    scope.setTriggerMode (TriggeredScope::None);
    scope.setNumSamplesPerPixel (256);
    scope.setVerticalZoomFactor (2.0);
    scope.setVerticalZoomOffset (-0.5, 0);
    scope.setVerticalZoomOffset (-0.5, 1);
    scope.setVerticalZoomOffset (-0.5, 2);
    scope.setColour (TriggeredScope::traceColourId + 0, Colours::transparentBlack);
    scope.setColour (TriggeredScope::envelopeColourId + 0, Colours::orange);
    scope.setColour (TriggeredScope::traceColourId + 1, Colours::transparentBlack);
    scope.setColour (TriggeredScope::envelopeColourId + 1, Colours::white);
    scope.setColour (TriggeredScope::traceColourId + 2, Colours::red);
    scope.setColour (TriggeredScope::envelopeColourId + 2, Colours::transparentBlack);

    setGridSize (7, 2);

	for (auto pp : limProc.getPluginParameters())
        pp->addListener (this);
}

LimiterAudioProcessorEditor::~LimiterAudioProcessorEditor()
{
    for (auto p : limProc.getPluginParameters())
        p->removeListener (this);
}

//==============================================================================
void LimiterAudioProcessorEditor::parameterChanged (Parameter*)
{
    meter.repaint();
}

void LimiterAudioProcessorEditor::resized()
{
    gin::ProcessorEditor::resized();

    componentForParam (*limProc.input)->setBounds (getGridArea (0, 0));
    componentForParam (*limProc.attack)->setBounds (getGridArea (2, 0));
    componentForParam (*limProc.release)->setBounds (getGridArea (3, 0));
    componentForParam (*limProc.threshold)->setBounds (getGridArea (4, 0));
    componentForParam (*limProc.output)->setBounds (getGridArea (6, 0));
    
    auto rc = getGridArea (0, 1, 7, 1);
    
    inputMeter.setBounds (rc.removeFromLeft (16));
    rc.removeFromLeft (4);
    
    meter.setBounds (rc.removeFromLeft (rc.getHeight()));
    rc.removeFromLeft (4);

    reductionMeter.setBounds (rc.removeFromLeft (16));
    rc.removeFromLeft (4);
    
    outputMeter.setBounds (rc.removeFromLeft (16));
    rc.removeFromLeft (4);
    
    scope.setBounds (rc);
}
