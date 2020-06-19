#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MeterNeedle : public Component
{
public:

    MeterNeedle();
    void prepare(const float& s, const float& e);
    void paint(Graphics& g) override;
    void resized() override;
    void update(const float& val);
    void redrawNeedle(Graphics& g, float centreX, float centreY, float length);
    void setMode(int m);
private:
    Rectangle<int> area;
    Colour statusOutline;
    float valueInDecibel;
    int mode;
    int minValue, maxValue;
    float sAngle, eAngle;
};
