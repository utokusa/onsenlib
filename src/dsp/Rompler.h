/*
  ==============================================================================

   Rompler

  ==============================================================================
*/

#pragma once

#include "../synth/SynthParams.h"
#include "DspCommon.h"

namespace onsen
{
//==============================================================================
class IRompler
{
    using flnum = float;

public:
    virtual flnum romplerVal (int sampleIdx /*sample index for playback sample rate*/) = 0;
    virtual void setCurrentPlaybackSampleRate (double sampleRate) = 0;
};
} // namespace onsen
