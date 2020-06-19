#include "include/LevelEnvelopeFollower.h"

#include <cassert>
#include <cmath>

void SimpleEnvFollower::prepare(const double& fs)
{
	sampleRate = fs;

	peakDecayInSamples = static_cast<int>(peakDecayInSeconds * sampleRate);
	peakDecay = 1.0f - 1.0f / static_cast<float>(peakDecayInSamples);

	rmsDecayInSamples = static_cast<int>(rmsDecayInSeconds * sampleRate);
	rmsDecay = 1.0f - 1.0f / static_cast<float>(rmsDecayInSamples);
}

void SimpleEnvFollower::setPeakDecay(float dc)
{
	peakDecayInSeconds = dc;
	prepare(sampleRate);
}

void SimpleEnvFollower::setRmsDecay(float dc)
{
	rmsDecayInSeconds = dc;
	prepare(sampleRate);
}

void SimpleEnvFollower::updatePeak(const float* const* channelData, int numChannels, int numSamples)
{
	assert(numChannels >= 0 && numSamples >= 0 && channelData != nullptr);
	if (numChannels > 0 && numSamples > 0)
	{
		for (int i = 0; i < numSamples; ++i)
		{
			float sum = 0.0f;
			for (int j = 0; j < numChannels; ++j)
				sum += std::abs(channelData[j][i]);

			sum /= static_cast<float>(numChannels);

			if (sum > currMaxPeak)
				currMaxPeak = sum;
			else if (currMaxPeak > 0.001f)
				currMaxPeak *= peakDecay;
			else currMaxPeak = 0.0f;
			//DBG("Current Maxpeak: " << currMaxPeak);
		}
	}
}

void SimpleEnvFollower::updateRMS(const float* const* channelData, int numChannels, int numSamples)
{
	assert(numChannels >= 0 && numSamples >= 0 && channelData != nullptr);
	if (numChannels > 0 && numSamples > 0)
	{
		for (int i = 0; i < numSamples; ++i)
		{
			float sum = 0.0f;
			for (int j = 0; j < numChannels; ++j)
				sum += std::abs(channelData[j][i]);

			sum /= static_cast<float>(numChannels);
			sum *= sum;

			if (sum > currMaxRMS)
				currMaxRMS = sum * rmsDecay;
			else if (currMaxRMS > 0.001f)
				currMaxRMS *= peakDecay;
			else currMaxRMS = 0.0f;
		}
	}
}

float SimpleEnvFollower::getPeak()
{
	return currMaxPeak;
}

float SimpleEnvFollower::getRMS()
{
	return sqrt(currMaxRMS);
}
