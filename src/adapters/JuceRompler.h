/*
  ==============================================================================

   Rompler

  ==============================================================================
*/

#pragma once

#include "../dsp/DspCommon.h"
#include "../dsp/Rompler.h"
#include "../synth/SynthParams.h"
#include <JuceHeader.h>
#include <memory>

namespace onsen
{
// You need to put sample as "Onsen Audio/OnsenlibSynth/samples/sample.wav" to play sample
class JuceRompler : public IRompler
{
    using flnum = float;

public:
    JuceRompler() : sampleRate (DEFAULT_SAMPLE_RATE),
                    sampleFile (juce::File::getSpecialLocation (
                                    juce::File::SpecialLocationType::userApplicationDataDirectory)
                                    .getChildFile ("Onsen Audio/OnsenlibSynth/samples/sample.wav")),
                    afm(),
                    source ((afm.registerBasicFormats(), afm.createReaderFor (sampleFile))),
                    sourceSampleRate (source ? source->sampleRate : 0.0),
                    length (source ? source->lengthInSamples : 0.0),
                    data (source ? std::min (2, int (source->numChannels)) : 2, length + 4)
    {
        if (length)
            source->read (&data, 0, length + 4, 0, true, true);
    }

    flnum romplerVal (int sampleIdx /*sample index for playback sample rate*/) override
    {
        if (! length)
            return 0.0;
        int sourceSampleIdx = (flnum) sampleIdx / sampleRate * sourceSampleRate;
        if (sourceSampleIdx < length)
        {
            int channel = 0;
            return (data.getSample (channel, sourceSampleIdx));
        }
        return 0.0;
    }

    void setCurrentPlaybackSampleRate (double _sampleRate) override
    {
        sampleRate = _sampleRate;
    }

private:
    juce::File sampleFile;
    juce::AudioFormatManager afm;
    std::unique_ptr<juce::AudioFormatReader> source;
    double sampleRate;
    double sourceSampleRate;
    int length;
    juce::AudioBuffer<float> data;
};
} // namespace onsen
