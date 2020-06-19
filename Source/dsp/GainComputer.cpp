#include "include/GainComputer.h"
#include <algorithm>
#include <limits>
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"

GainComputer::GainComputer()
{
    threshold = -20.0f;
    ratio = 2.0f;
    slope = 1.0f / ratio - 1.0f;
    knee = 6.0f;
    kneeHalf = 3.0f;
}

void GainComputer::setThreshold(float newTreshold)
{
    threshold = newTreshold;
}

void GainComputer::setRatio(float newRatio)
{
    if (ratio != newRatio)
    {
        ratio = newRatio;
        if (ratio > 23.9f) ratio = -std::numeric_limits<float>::infinity();
        slope = 1.0f / newRatio - 1.0f;
    }
}

void GainComputer::setKnee(float newKnee)
{
    if (newKnee != knee)
    {
        knee = newKnee;
        kneeHalf = newKnee / 2.0f;
    }
}

float GainComputer::applyCompression(float& input)
{
    const float overshoot = input - threshold;

    if (overshoot <= -kneeHalf)
        return 0.0f;
    if (overshoot > -kneeHalf && overshoot <= kneeHalf)
        return 0.5f * slope * ((overshoot + kneeHalf) * (overshoot + kneeHalf)) / knee;


    return slope * overshoot;
}

void GainComputer::applyCompressionToBuffer(float* src, int numSamples)
{
    for (int i = 0; i < numSamples; ++i)
    {
        const float level = std::max(abs(src[i]), 1e-6f);
        float levelInDecibels = Decibels::gainToDecibels(level);
        src[i] = applyCompression(levelInDecibels);
    }
}
