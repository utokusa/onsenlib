/*
  ==============================================================================

   Oscillator Parameters Mcok

  ==============================================================================
*/

#pragma once

#include "OscillatorParams.h"

namespace onsen
{
struct OscillatorParamsMock : public IOscillatorParams
{
    OscillatorParamsMock (
        flnum sinGain,
        flnum squareGain,
        flnum sawGain,
        flnum subSquareGain,
        flnum noiseGain,
        flnum shape,
        bool antiAliasOn) : sinGain (sinGain),
                            squareGain (squareGain),
                            sawGain (sawGain),
                            subSquareGain (subSquareGain),
                            noiseGain (noiseGain),
                            shape (shape),
                            antiAliasOn (antiAliasOn) {}

    flnum getSinGain() const override { return sinGain; }
    flnum getSquareGain() const override { return squareGain; }
    flnum getSawGain() const override { return sawGain; }
    flnum getSubSquareGain() const override { return subSquareGain; }
    flnum getNoiseGain() const override { return noiseGain; }
    flnum getShape() const override { return shape; }
    bool getAntiAliasOn() const override { return antiAliasOn; }

    flnum sinGain;
    flnum squareGain;
    flnum sawGain;
    flnum subSquareGain;
    flnum noiseGain;
    flnum shape;
    bool antiAliasOn;
};

} // namespace onsen
