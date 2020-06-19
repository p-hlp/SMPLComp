/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SmplcompAudioProcessorEditor::SmplcompAudioProcessorEditor(SmplcompAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor(p), valueTreeState(vts), backgroundApp(Colour(Constants::Colors::bg_App)),
      inGainLSlider(this), makeupGainLSlider(this),
      threshLSlider(this), ratioLSlider(this), kneeLSlider(this), attackLSlider(this), releaseLSlider(this),
      mixLSlider(this)
{
    setLookAndFeel(&LAF);
    initWidgets();
    setSize(400, 260);
    startTimerHz(60);
}

SmplcompAudioProcessorEditor::~SmplcompAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void SmplcompAudioProcessorEditor::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(backgroundApp);
}

void SmplcompAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(Constants::Margins::big);

    const auto btnAreaWidth = area.getWidth() / 5;
    const auto btnBotHeight = area.getHeight() / 3;

    auto lBtnArea = area.removeFromLeft(btnAreaWidth).reduced(Constants::Margins::small);
    auto rBtnArea = area.removeFromRight(btnAreaWidth).reduced(Constants::Margins::small);
    auto botBtnArea = area.removeFromBottom(btnBotHeight).reduced(Constants::Margins::medium);

    const FlexItem::Margin knobMargin = FlexItem::Margin(Constants::Margins::small);
    const FlexItem::Margin knobMarginSmall = FlexItem::Margin(Constants::Margins::medium);


    FlexBox leftBtnBox;
    leftBtnBox.flexWrap = FlexBox::Wrap::noWrap;
    leftBtnBox.flexDirection = FlexBox::Direction::column;
    leftBtnBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    leftBtnBox.items.add(FlexItem(attackLSlider).withFlex(1).withMargin(knobMarginSmall));
    leftBtnBox.items.add(FlexItem(releaseLSlider).withFlex(1).withMargin(knobMarginSmall));
    leftBtnBox.items.add(FlexItem(inGainLSlider).withFlex(1).withMargin(knobMarginSmall));
    leftBtnBox.performLayout(lBtnArea.toFloat());

    FlexBox rightBtnBox;
    rightBtnBox.flexWrap = FlexBox::Wrap::noWrap;
    rightBtnBox.flexDirection = FlexBox::Direction::column;
    rightBtnBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    rightBtnBox.items.add(FlexItem(kneeLSlider).withFlex(1).withMargin(knobMarginSmall));
    rightBtnBox.items.add(FlexItem(ratioLSlider).withFlex(1).withMargin(knobMarginSmall));
    rightBtnBox.items.add(FlexItem(mixLSlider).withFlex(1).withMargin(knobMarginSmall));
    rightBtnBox.performLayout(rBtnArea.toFloat());

    FlexBox botBtnBox;
    botBtnBox.flexWrap = FlexBox::Wrap::noWrap;
    botBtnBox.flexDirection = FlexBox::Direction::row;
    botBtnBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    botBtnBox.items.add(FlexItem(threshLSlider).withFlex(1));
    botBtnBox.items.add(FlexItem(makeupGainLSlider).withFlex(1));
    botBtnBox.performLayout(botBtnArea.toFloat());

    FlexBox meterBox;
    meterBox.flexWrap = FlexBox::Wrap::noWrap;
    meterBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    meterBox.items.add(FlexItem(meter).withFlex(1).withMargin(Constants::Margins::big));
    meterBox.performLayout(area.toFloat());
}


void SmplcompAudioProcessorEditor::timerCallback()
{
    int m = meter.getMode();
    switch (m)
    {
    case Meter::Mode::IN:
        //DBG("IN: " << processor.currentInput.get());
        meter.update(processor.currentInput.get());
        break;
    case Meter::Mode::OUT:
        //DBG("OUT: " << processor.currentOutput.get());
        meter.update(processor.currentOutput.get());
        break;
    case Meter::Mode::GR:
        //DBG("GR: " << processor.gainReduction.get());
        meter.update(processor.gainReduction.get());
        break;
    default:
        break;
    }
}

void SmplcompAudioProcessorEditor::initWidgets()
{
    addAndMakeVisible(inGainLSlider);
    inGainLSlider.reset(valueTreeState, "inputgain");
    inGainLSlider.setLabelText("Input");

    addAndMakeVisible(makeupGainLSlider);
    makeupGainLSlider.reset(valueTreeState, "makeup");
    makeupGainLSlider.setLabelText("Makeup");

    addAndMakeVisible(threshLSlider);
    threshLSlider.reset(valueTreeState, "threshold");
    threshLSlider.setLabelText("Threshold");

    addAndMakeVisible(ratioLSlider);
    ratioLSlider.reset(valueTreeState, "ratio");
    ratioLSlider.setLabelText("Ratio");

    addAndMakeVisible(kneeLSlider);
    kneeLSlider.reset(valueTreeState, "knee");
    kneeLSlider.setLabelText("Knee");

    addAndMakeVisible(attackLSlider);
    attackLSlider.reset(valueTreeState, "attack");
    attackLSlider.setLabelText("Attack");

    addAndMakeVisible(releaseLSlider);
    releaseLSlider.reset(valueTreeState, "release");
    releaseLSlider.setLabelText("Release");

    addAndMakeVisible(mixLSlider);
    mixLSlider.reset(valueTreeState, "mix");
    mixLSlider.setLabelText("Mix");

    addAndMakeVisible(meter);
    meter.setMode(Meter::Mode::GR);
}
