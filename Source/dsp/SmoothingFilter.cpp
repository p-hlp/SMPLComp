#include "include/SmoothingFilter.h"
#include "../JuceLibraryCode/JuceHeader.h"

void SmoothingFilter::prepare(const double& fs)
{
    sampleRate = fs;
    a1 = 1;
    b1 = 1 - a1;
}

void SmoothingFilter::process(const double& sample)
{
    if (first)
    {
        state = sample;
        first = false;
    }
    state = a1 * sample + b1 * state;
}

double SmoothingFilter::getState()
{
    return state;
}

void SmoothingFilter::setAlpha(double a)
{
    a1 = a;
    b1 = 1 - a1;
}

void SmoothingFilter::setAlphaWithTime(float timeInSeconds)
{
    a1 = exp(-1.0 / (sampleRate * timeInSeconds));
    b1 = 1 - a1;
}
