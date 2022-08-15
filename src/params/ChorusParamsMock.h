/*
  ==============================================================================

   Chorus Parameters Mock

  ==============================================================================
*/

#pragma once

#include "../dsp/DspCommon.h"
#include "ChorusParams.h"

namespace onsen
{
//==============================================================================
struct ChorusParamsMock : public IChorusParams
{
    bool getChorusOn() const override { return true; }
    flnum getDelayTime_msec() const override { return 15.0; }
    flnum getFeedback() const override { return 0.3; }
    flnum getDepth() const override { return 0.1; };
    flnum getRate() const override { return 0.5; };
    flnum getDryWet() const override { return 0.5; };
    // For buffer size. The return value should be always the same.
    // In ideal, it should be constexpr virtual function.
    flnum getMaxDelayTime_msec() const override { return 20.0; };
};
} // namespace onsen
