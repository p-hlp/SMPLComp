#pragma once

/* Basic envelope-follwer, to track peak & rms signal level with configurable decay time*/
class SimpleEnvFollower
{
public:
	SimpleEnvFollower() = default;

	// Prepares envelope follower with given sample rate and recalculates decayInSamples
	// aswell as the peak/rms coefficient
	void prepare(const double& fs);

	// Set peak decay
	void setPeakDecay(float dc);

	// Set rms decay
	void setRmsDecay(float dc);

	// Updates peak envelope follower from given audio buffer
	void updatePeak(const float* const* channelData, int numChannels, int numSamples);

	// Updates rms envelope follower from given audio buffer
	void updateRMS(const float* const* channelData, int numChannels, int numSamples);

	// Gets current peak, call after updatePeak
	float getPeak();

	// Gets current rms, vall after updateRMS
	float getRMS();

private:
	float currMaxPeak{ 0.0f };
	float currMaxRMS{ 0.0f };
	float peakDecay{ 0.99992f };
    float rmsDecay{ 0.95f };
	float peakDecayInSeconds{ 0.5f };
    float rmsDecayInSeconds{ 0.0f };
	int peakDecayInSamples{ 0 };
    int rmsDecayInSamples{ 0 };
	double sampleRate{ 0.0f };
};

