/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SmplcompAudioProcessorEditor::SmplcompAudioProcessorEditor (SmplcompAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts), backgroundApp(Colour(Constants::Colors::bg_App)), inGainLSlider(this), makeupGainLSlider(this),
    treshLSlider(this), ratioLSlider(this), kneeLSlider(this), attackLSlider(this), releaseLSlider(this),
    mixLSlider(this), powerButton("powerButton", DrawableButton::ButtonStyle::ImageOnButtonBackground)
{
    setLookAndFeel(&LAF);
    initWidgets();
    startTimerHz(60);
    setSize (400, 300);
}

SmplcompAudioProcessorEditor::~SmplcompAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void SmplcompAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(backgroundApp);
}

void SmplcompAudioProcessorEditor::resized()
{
	auto area = getLocalBounds().reduced(Constants::Margins::big);

	const auto headerHeight = area.getHeight() / 10;
	const auto btnAreaWidth = area.getWidth() / 5;
	const auto btnBotHeight = area.getHeight() / 3;

	auto header = area.removeFromTop(headerHeight).reduced(Constants::Margins::small);
	auto lBtnArea = area.removeFromLeft(btnAreaWidth).reduced(Constants::Margins::small);
	auto rBtnArea = area.removeFromRight(btnAreaWidth).reduced(Constants::Margins::small);
	auto botBtnArea = area.removeFromBottom(btnBotHeight).reduced(Constants::Margins::medium);

	const FlexItem::Margin knobMargin = FlexItem::Margin(Constants::Margins::medium);
	const FlexItem::Margin knobMarginSmall = FlexItem::Margin(Constants::Margins::big);
	const FlexItem::Margin buttonMargin = FlexItem::Margin(Constants::Margins::small, Constants::Margins::big,
		Constants::Margins::small,
		Constants::Margins::big);
	FlexBox headerBox;
	headerBox.flexWrap = FlexBox::Wrap::noWrap;
	headerBox.flexDirection = FlexBox::Direction::row;
	headerBox.justifyContent = FlexBox::JustifyContent::spaceAround;
	headerBox.items.add(FlexItem(powerButton).withFlex(1).withMargin(buttonMargin));
	headerBox.performLayout(header.toFloat());

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
	botBtnBox.items.add(FlexItem(treshLSlider).withFlex(1).withMargin(knobMargin));
	botBtnBox.items.add(FlexItem(makeupGainLSlider).withFlex(1).withMargin(knobMargin));
	botBtnBox.performLayout(botBtnArea.toFloat());

	FlexBox meterBox;
	meterBox.flexWrap = FlexBox::Wrap::noWrap;
	meterBox.justifyContent = FlexBox::JustifyContent::spaceAround;
	meterBox.items.add(FlexItem(meter).withFlex(1).withMargin(Constants::Margins::big));
	meterBox.performLayout(area.toFloat());
}


void SmplcompAudioProcessorEditor::buttonClicked(Button* b)
{
	// Disable UI when power turned off
	if (b == &powerButton)
	{
		inGainLSlider.setEnabled(!inGainLSlider.isEnabled());
		makeupGainLSlider.setEnabled(!makeupGainLSlider.isEnabled());
		treshLSlider.setEnabled(!treshLSlider.isEnabled());
		ratioLSlider.setEnabled(!ratioLSlider.isEnabled());
		kneeLSlider.setEnabled(!kneeLSlider.isEnabled());
		attackLSlider.setEnabled(!attackLSlider.isEnabled());
		releaseLSlider.setEnabled(!releaseLSlider.isEnabled());
		mixLSlider.setEnabled(!mixLSlider.isEnabled());
	}
}

void SmplcompAudioProcessorEditor::timerCallback()
{
}

void SmplcompAudioProcessorEditor::initWidgets()
{
	addAndMakeVisible(inGainLSlider);
	inGainLSlider.reset(valueTreeState, "inputgain");
	inGainLSlider.setLabelText("Input");

	addAndMakeVisible(makeupGainLSlider);
	makeupGainLSlider.reset(valueTreeState, "makeup");
	makeupGainLSlider.setLabelText("Makeup");

	addAndMakeVisible(treshLSlider);
	treshLSlider.reset(valueTreeState, "threshold");
	treshLSlider.setLabelText("Threshold");

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

	addAndMakeVisible(powerButton);
	powerButton.setColour(TextButton::ColourIds::buttonColourId, Colour::fromRGB(245, 124, 0));
	powerButton.setImages(
		Drawable::createFromImageData(BinaryData::power_white_svg, BinaryData::power_white_svgSize).get());
	powerButton.setClickingTogglesState(true);
	powerButton.setToggleState(true, dontSendNotification);
	powerButton.addListener(this);
	powerAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "power", powerButton));

	addAndMakeVisible(meter);
	meter.setMode(Meter::Mode::GR);
}
