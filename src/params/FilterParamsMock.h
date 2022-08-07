/*
  ==============================================================================

   Filter Parameters Mock

  ==============================================================================
*/

#pragma once

#include "../dsp/DspCommon.h"
#include "FilterParams.h"

namespace onsen
{
//==============================================================================
class FilterParamsMock : public IFilterParams
{
public:
    FilterParamsMock (bool filterOn = true) : filterOn (filterOn) {}

    flnum getControlledFrequency (flnum controlVal) const override
    {
        return 100.0;
    }

    flnum getResonance() const override
    {
        return 2.0;
    }

    flnum getFilterEnvelope() const override
    {
        return 0.5f;
    }

    bool getFilterOn() const override
    {
        return filterOn;
    }

    void setFilterOn (bool val)
    {
        filterOn = val;
    }

private:
    bool filterOn;
};
} // namespace onsen
