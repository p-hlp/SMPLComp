#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DelayLine
{
public:

    DelayLine() = default;

    // Prepares delayline with ProcessSpec-Object, resizes delay-buffer, recalculates delayInSamples
    // and resets writePosition
    void prepare(const dsp::ProcessSpec& spec);

    // Delays given AudioBuffer by delayInSamples samples
    void process(AudioBuffer<float>& buffer);

    // Sets delay
    void setDelay(float delayInSeconds);

private:
    void pushSamples(const AudioBuffer<float>& srcBuffer, int nSam, int nCh);
    void readSamples(AudioBuffer<float>& dstBuffer, int nSam, int nCh);

    inline void getReadBlockSize(int numSamples, int& index, int& block1, int& block2);
    inline void getWriteBlockSize(int numSamples, int& index, int& block1, int& block2);

private:
    //Directly initialize process spec to avoid debugging problems
    dsp::ProcessSpec procSpec{ -1, 0, 0 };

    AudioBuffer<float> delayBuffer;
    int delayBufferSize{ 0 };
    int delayInSamples{ 0 };
    float delayInSeconds{ 0.0f };
    int writePosition{ 0 };
    bool isBypassed{ true };
};
