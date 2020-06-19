#pragma once

/*Simple exponential moving average filter, also known as 1-pole iir filter
 * This class can be used to smooth values over a certain time frame
 */
class SmoothingFilter
{
public:

    SmoothingFilter() = default;

    // Prepares the SmoothingFilter with a sampleRate
    void prepare(const double& fs);

    // Processes a given sample
    void process(const double& sample);

    // Sets coefficient manually
    void setAlpha(double a);

    // Set time-frame in seconds, recalculates needed coefficients
    void setAlphaWithTime(float timeInSeconds);

    // Gets current value
    double getState();

private:
    double a1{ 1.0 }, b1{ 0.0 };
    double state{ 0.0 };
    double sampleRate{ 0.0 };
    bool first{ true };
};
