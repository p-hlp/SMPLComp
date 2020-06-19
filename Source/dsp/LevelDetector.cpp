#include "include/LevelDetector.h"
#include "../JuceLibraryCode/JuceHeader.h"

void LevelDetector::prepare(const double& fs)
{
    sampleRate = fs;
    alphaAttack = exp(-1.0 / (sampleRate * attackTimeInSeconds));
    alphaRelease = exp(-1.0 / (sampleRate * releaseTimeInSeconds));
    state01 = 0.0;
    state02 = 0.0;
}

void LevelDetector::setAttack(const double& attack)
{
    if (attack != attackTimeInSeconds)
    {
        attackTimeInSeconds = attack;    //Time it takes to reach 1-1/e = 0.63
        alphaAttack = exp(-1.0 / (sampleRate * attackTimeInSeconds));        //aA = e^(-1/TA*fs)
    }
}

void LevelDetector::setRelease(const double& release)
{
    if (release != releaseTimeInSeconds)
    {
        releaseTimeInSeconds = release;        //Time it takes to reach 1 - (1-1/e) = 0.37
        alphaRelease = exp(-1.0 / (sampleRate * releaseTimeInSeconds));    //aR = e^(-1/TR*fs)
    }
}


double LevelDetector::getAttack()
{
    return attackTimeInSeconds;
}

double LevelDetector::getRelease()
{
    return releaseTimeInSeconds;
}

double LevelDetector::getAlphaAttack()
{
    return alphaAttack;
}

double LevelDetector::getAlphaRelease()
{
    return alphaRelease;
}

float LevelDetector::processPeakBranched(const float& in)
{
    //Smooth branched peak detector
    if (in < state01)
        state01 = alphaAttack * state01 + (1 - alphaAttack) * in;
    else
        state01 = alphaRelease * state01 + (1 - alphaRelease) * in;

    return static_cast<float>(state01);    //y_L
}


float LevelDetector::processPeakDecoupled(const float& in)
{
    //Smooth decoupled peak detector
    const double input = static_cast<double>(in);
    state02 = jmax(input, alphaRelease * state02 + (1 - alphaRelease) * input);
    state01 = alphaAttack * state01 + (1 - alphaAttack) * state02;
    return static_cast<float>(state01);
}

void LevelDetector::applyBallistics(float* src, int numSamples)
{
    // Apply ballistics to src buffer
    for (int i = 0; i < numSamples; ++i)
        src[i] = processPeakBranched(src[i]);
}