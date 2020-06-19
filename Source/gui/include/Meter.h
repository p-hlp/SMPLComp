#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "MeterNeedle.h"
#include "MeterBackground.h"


class Meter : public Component
{
public:
	enum Mode { IN = 1, OUT, GR };
	Meter();
	void paint(Graphics& g) override;
	void resized() override;
	void setMode(int m);
	void modeBoxChanged();
	void update(const float& val);
	int getMode();
	float getValue();
private:
	MeterBackground meterBg;
	MeterNeedle needle;
	ComboBox modeBox;
	Colour backgroundDarkGrey;
	int meterMode;
	float valueInDecibel;
	float startAngle, endAngle;
};
