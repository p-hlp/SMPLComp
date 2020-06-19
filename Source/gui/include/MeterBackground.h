#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MeterBackground : public Component
{
public:

    MeterBackground();
    void prepare(const float& s, const float& e);
    void paint(Graphics& g) override;
    void resized() override;
    void drawIndicators(Graphics& g, float centreX, float centreY, float length);
    void setMode(int m);
private:
    Rectangle<int> meterArea;
    Colour backgroundLightGrey, backgroundApp;
    int mode;
    int minValue, maxValue;
    float sAngle, eAngle;
    int step;
};
