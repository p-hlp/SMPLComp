#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ModSlider.h"

using SliderAttachment = std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>;
using ButtonAttachment = std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment>;

class LabeledSlider : public Component
{
public:

	LabeledSlider() : slider(&sliderLabel)
	{
		addAndMakeVisible(slider);
		slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
		slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

		addAndMakeVisible(sliderLabel);
		sliderLabel.setJustificationType(Justification::centred);
	}

	LabeledSlider(Component* parent) : slider(&sliderLabel)
	{
		addAndMakeVisible(slider);
		slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
		slider.setPopupDisplayEnabled(true, true, parent, 0);
		slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

		addAndMakeVisible(sliderLabel);
		sliderLabel.setJustificationType(Justification::centred);
	}

	void reset(AudioProcessorValueTreeState& state, const String& paramID)
	{
		sAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(state, paramID, slider));
	}

	void setLabelText(const String& text)
	{
		sliderLabel.setText(text, dontSendNotification);
	}


	void resized() override
	{
		auto bounds = getLocalBounds().reduced(2);
		const auto fontHeight = sliderLabel.getFont().getHeight();

		const auto labelBounds = bounds.removeFromBottom(fontHeight);
		slider.setBounds(bounds);
		sliderLabel.setBounds(labelBounds);
	}

	void setHasModifier(bool mod) { slider.setHasModifiers(mod); }
	bool hasModifier() const { return slider.hasModifier(); }

private:
	ModSlider slider;
	Label sliderLabel;
	SliderAttachment sAttachment;
	ButtonAttachment bAttachment;
};