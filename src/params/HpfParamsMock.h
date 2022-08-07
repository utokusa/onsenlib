/*
  ==============================================================================

   HPF Parameters Mock

  ==============================================================================
*/

#pragma once

#include "../dsp/DspCommon.h"
#include "HpfParams.h"

namespace onsen
{
//==============================================================================
struct HpfParamsMock : public IHpfParams
{
    bool hpfOn = true;

    flnum getFrequency() const override
    {
        return 300.0;
    }

    bool getHpfOn() const override
    {
        return hpfOn;
    }
};
} // namespace onsen
