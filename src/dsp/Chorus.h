/*
  ==============================================================================

   Chorus

  ==============================================================================
*/

#pragma once

#include "../synth/SynthParams.h"
#include "DspCommon.h"
#include "IAudioBuffer.h"
#include <vector>

namespace onsen
{
//==============================================================================
class Chorus
{
    struct ChorusLfo
    {
    public:
        flnum val() const
        {
            return sinWave (currentAngle);
        }

        void update()
        {
            currentAngle += angleDelta();
            if (currentAngle > 2.0 * pi)
                currentAngle -= 2.0 * pi;
        }

    private:
        flnum angleDelta() const
        {
            return 2.0 * pi * p->getRate() / sampleRate;
        }

        static flnum sinWave (flnum angle)
        {
            return std::sin (angle);
        }

    public:
        flnum currentAngle;
        const IChorusParams* p;
        const flnum& sampleRate;
    };

public:
    Chorus (const IChorusParams* chorusParam)
        : sampleRate (DEFAULT_SAMPLE_RATE),
          p (chorusParam),
          writePointer (0),
          lfo ({ 0.0, p, sampleRate }),
          interpolateBufferAccess (true)
    {
        prepare();
    };

    void render (IAudioBuffer* outputAudio, int startSample, int numSamples);
    void setCurrentPlaybackSampleRate (double _sampleRate);

private:
    flnum sampleRate;
    const IChorusParams* p;
    std::vector<flnum> buf;
    int writePointer;
    ChorusLfo lfo;
    bool interpolateBufferAccess;

    //==============================================================================
    void prepare();

    inline int delaySample()
    {
        flnum valueZeroToOne = (1.0 + p->getDepth() * lfo.val()) / 2.0;
        valueZeroToOne = std::clamp (static_cast<double> (valueZeroToOne), 0.0, 1.0);
        return static_cast<int> (p->getDelayTime_msec() * valueZeroToOne / 1000.0 * sampleRate);
    }

    inline int readIdx()
    {
        const int idx = writePointer - delaySample();
        return idx >= 0 ? idx : idx + static_cast<int> (buf.size());
    }

    inline flnum getModDelayValueWithoutInterpolation()
    {
        return buf.at (readIdx());
    }

    inline flnum delayTimeInSec()
    {
        flnum valueZeroToOne = (1.0 + p->getDepth() * lfo.val()) / 2.0;
        valueZeroToOne = std::clamp (static_cast<double> (valueZeroToOne), 0.0, 1.0);
        const auto ret = p->getDelayTime_msec() * valueZeroToOne / 1000.0;
        return ret;
    }

    inline int firstReadIdx (const flnum delayTimeInSample)
    {
        const int idx = writePointer - (static_cast<int> (delayTimeInSample) + 1);

        return idx >= 0 ? idx : idx + static_cast<int> (buf.size());
    }

    inline flnum firstReadSampleRatio (const flnum delayTimeInSample)
    {
        return delayTimeInSample - std::floor (delayTimeInSample);
    }

    inline flnum getBufValueWithInterpolation (int firstIdx, int secondIdx, flnum firstRatio)
    {
        // [Circuit Bending]
        // return buf.at(firstIdx) * firstIdx + buf.at(secondIdx) * (1.0 - firstIdx);
        return buf.at (firstIdx) * firstRatio + buf.at (secondIdx) * (1.0 - firstRatio);
    }

    inline flnum getModDelayValueWithInterpolation()
    {
        // Use linear interpolation
        // https://ccrma.stanford.edu/~jos/pasp/Delay_Line_Interpolation.html
        const flnum delayTimeInSample = delayTimeInSec() * sampleRate;
        const flnum firstIdx = firstReadIdx (delayTimeInSample);
        const flnum secondIdx = (firstIdx == static_cast<int> (buf.size()) - 1) ? 0 : firstIdx + 1;
        const flnum firstRatio = firstReadSampleRatio (delayTimeInSample);
        return getBufValueWithInterpolation (firstIdx, secondIdx, firstRatio);
    }

    inline flnum getModDelayValue()
    {
        if (interpolateBufferAccess)
        {
            return getModDelayValueWithInterpolation();
        }
        else
        {
            // It has zipper noise
            return getModDelayValueWithoutInterpolation();
        }
    }
};
} // namespace onsen
