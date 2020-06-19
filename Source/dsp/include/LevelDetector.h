#pragma once
#include "SmoothingFilter.h"


/*LevelDetector Class:
 * Used to have a smooth representation of the level
 * Might be used in linear or log. domain
 * In this compressor implementation it's used in log. domain after the gain computer to smooth the calculated attenuations,
 * therefore the detector does not have to work on the whole dynamic range of the input signal
 */
class LevelDetector
{
public:
    LevelDetector() = default;

    // Prepares LevelDetector with a ProcessSpec-Object containing samplerate, blocksize and number of channels
    void prepare(const double& fs);

    // Sets attack time constant
    void setAttack(const double&);

    // Sets release time constant
    void setRelease(const double&);

    // Gets current attack time constant
    double getAttack();

    // Gets current release time constant
    double getRelease();

    // Gets calculated attack coefficient
    double getAlphaAttack();

    // gets calculated release coefficient
    double getAlphaRelease();

    // Processes a sample with smooth branched peak detector
    float processPeakBranched(const float&);

    // Processes a sample with smooth decoupled peak detector
    float processPeakDecoupled(const float&);

    // Applies ballistics to given buffer
    void applyBallistics(float*, int);

private:
    double attackTimeInSeconds{ 0.01 }, alphaAttack{ 0.0 };
    double releaseTimeInSeconds{ 0.14 }, alphaRelease{ 0.0 };
    double state01{ 0.0 }, state02{ 0.0 };
    double sampleRate{ 0.0 };
    bool autoAttack{ false };
    bool autoRelease{ false };
};
