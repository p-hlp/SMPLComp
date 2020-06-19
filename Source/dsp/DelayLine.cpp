#include "include/DelayLine.h"

void DelayLine::prepare(const dsp::ProcessSpec& spec)
{
    procSpec = spec;
    delayInSamples = static_cast<int>(spec.sampleRate * delayInSeconds);
    delayBufferSize = static_cast<int>(spec.maximumBlockSize) + delayInSamples;
    delayBuffer.setSize(spec.numChannels, delayBufferSize);
    delayBuffer.clear();
    writePosition = 0;
}

void DelayLine::process(AudioBuffer<float>& buffer)
{
    if (!isBypassed)
    {
        const auto numSamples = buffer.getNumSamples();
        const auto numChannels = buffer.getNumChannels();

        jassert(delayBuffer.getNumChannels() == numChannels);
        jassert(numSamples <= delayBufferSize);

        //write to delayBuffer from buffer
        pushSamples(buffer, numSamples, numChannels);

        //read from delayBuffer to buffer
        readSamples(buffer, numSamples, numChannels);

        //Increase writePosition, wrap if not within bounds of delayBuffer
        writePosition += numSamples;
        writePosition = writePosition % delayBufferSize;
    }
}

void DelayLine::setDelay(float delay)
{
    //Check if delay is valid, otherwise bypass
    if (delay > 0.0f)
    {
        delayInSeconds = delay;
        isBypassed = false;
    }
    else
    {
        delayInSeconds = 0.0f;
        isBypassed = true;
    }

    //Prepare delayBuffer with processing specs
    prepare(procSpec);
}

void DelayLine::pushSamples(const AudioBuffer<float>& srcBuffer, int nSam, int nCh)
{
    //b1 = samples before wrap, b2 = samples after wrap
    int index, b1, b2;
    getWriteBlockSize(nSam, index, b1, b2);
    //Write to delayBuffer with FloatVectorOperations
    for (int i = 0; i < nCh; ++i)
        FloatVectorOperations::copy(delayBuffer.getWritePointer(i) + index, srcBuffer.getReadPointer(i), b1);

    if (b2 > 0)
        for (int i = 0; i < nCh; ++i)
            //Copy rest of buffer to delayBuffer
            FloatVectorOperations::copy(delayBuffer.getWritePointer(i), srcBuffer.getReadPointer(i) + b1, b2);
}

void DelayLine::readSamples(AudioBuffer<float>& dstBuffer, int nSam, int nCh)
{
    //b1 = samples before wrap, b2 = samples after wrap
    int index, b1, b2;
    getReadBlockSize(nSam, index, b1, b2);
    for (int i = 0; i < nCh; i++)
        FloatVectorOperations::copy(dstBuffer.getWritePointer(i), delayBuffer.getReadPointer(i) + index, b1);

    if (b2 > 0)
        for (int i = 0; i < nCh; i++)
            FloatVectorOperations::copy(dstBuffer.getWritePointer(i) + b1, delayBuffer.getReadPointer(i), b2);
}

inline void DelayLine::getReadBlockSize(int numSamples, int& index, int& block1, int& block2)
{
    int pos = writePosition - delayInSamples;
    if (pos < 0)pos += delayBufferSize;
    pos = pos % delayBufferSize;
    //b1 can be max. number of samples in inputBuffer -> numSamples
    block1 = std::min(delayBufferSize - pos, numSamples);
    numSamples -= block1;
    //if b1 is not size of inputBuffer, calculate rest
    block2 = numSamples > 0 ? numSamples : 0;
    //set read/write start position
    index = pos;
}

inline void DelayLine::getWriteBlockSize(int numSamples, int& index, int& block1, int& block2)
{
    int pos = writePosition;
    if (pos < 0) pos += delayBufferSize;
    pos = pos % delayBufferSize;
    //b1 can be max. number of samples in inputBuffer -> numSamples
    block1 = std::min(delayBufferSize - pos, numSamples);
    numSamples -= block1;
    //if b1 is not size of inputBuffer, calculate rest
    block2 = numSamples > 0 ? numSamples : 0;
    //set read/write start position
    index = pos;
}
