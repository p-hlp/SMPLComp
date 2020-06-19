#pragma once

/* GainComputer Class:
 * Calculates the needed attenuation to compress a signal with given characteristics
 */
class GainComputer
{
public:

    GainComputer();

    // Sets the threshold in dB
    void setThreshold(float);

    // Sets the ratio in dB
    void setRatio(float);

    // Sets the knee-width in dB (if > 0, 2nd order interpolation for soft knee)
    void setKnee(float);

    // Applies characteristics to a given sample
    // returns attenuation
    float applyCompression(float&);

    void applyCompressionToBuffer(float*, int);

private:
    float threshold{ -20.0f };
    float ratio{ 2.0f };
    float knee{ 6.0f }, kneeHalf{ 3.0f };
    float slope{ -0.5f };
};
