/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


#include "gui/include/LabeledSlider.h"
#include "gui/include/Meter.h"
#include "gui/include/MeterBackground.h"
#include "gui/include/SMPLCompLookAndFeel.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SmplcompAudioProcessorEditor  : public AudioProcessorEditor, Timer
{
public:
    SmplcompAudioProcessorEditor (SmplcompAudioProcessor&, AudioProcessorValueTreeState&);
    ~SmplcompAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void initWidgets();
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SmplcompAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    SMPLCompLookAndFeel LAF;

    Colour backgroundApp;

    //Widgets
    MeterBackground meterbg;
    Meter meter;
    LabeledSlider inGainLSlider;
    LabeledSlider makeupGainLSlider;
    LabeledSlider threshLSlider;
    LabeledSlider ratioLSlider;
    LabeledSlider kneeLSlider;
    LabeledSlider attackLSlider;
    LabeledSlider releaseLSlider;
    LabeledSlider mixLSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SmplcompAudioProcessorEditor)
};
