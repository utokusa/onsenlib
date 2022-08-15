/*
  ==============================================================================

   Chorus Parameters

  ==============================================================================
*/

#pragma once

#include "../dsp/DspCommon.h"
#include "ParamCommon.h"
#include <atomic>
#include <vector>

namespace onsen
{
//==============================================================================
class IChorusParams
{
public:
    virtual bool getChorusOn() const = 0;
    virtual flnum getDelayTime_msec() const = 0;
    virtual flnum getFeedback() const = 0;
    virtual flnum getDepth() const = 0;
    virtual flnum getRate() const = 0;
    virtual flnum getDryWet() const = 0;
    // For buffer size. The return value should be always the same.
    // In ideal, it should be constexpr virtual function.
    virtual flnum getMaxDelayTime_msec() const = 0;
};

//==============================================================================
class ChorusParams : public IChorusParams
{
public:
    bool getChorusOn() const override
    {
        return chorusOnVal > 0.5;
    }

    void setChorusOnPtr (std::atomic<flnum>* _chorusOn)
    {
        chorusOn = _chorusOn;
        chorusOnVal = *chorusOn;
    }

    flnum getDelayTime_msec() const override
    {
        return convertNormalizedValToDelayTime_msec (delayTime_msecVal);
    }

    void setDelayTime_msecPtr (std::atomic<flnum>* _delayTime_msec)
    {
        delayTime_msec = _delayTime_msec;
        delayTime_msecVal = *delayTime_msec;
    }

    flnum getFeedback() const override
    {
        // TODO: 0 - 0.8, default: 0.3
        return convertNormalizedValToFeedback (feedbackVal);
    }

    void setFeedbackPtr (std::atomic<flnum>* _feedback)
    {
        feedback = _feedback;
        feedbackVal = *feedback;
    }

    flnum getDepth() const override
    {
        // TODO: 0 - 0.5, default: 0.1
        return convertNormalizedValToDepth (depthVal);
    }

    void setDepthPtr (std::atomic<flnum>* _depth)
    {
        depth = _depth;
        depthVal = *depth;
    }

    flnum getRate() const override
    {
        // [Hz]
        // TODO: default 0.5 Hz
        return lowestRateVal() * pow (rateBaseNumber(), rateVal);
    }

    void setRatePtr (std::atomic<flnum>* _rate)
    {
        rate = _rate;
        rateVal = *rate;
    }

    flnum getDryWet() const override
    {
        return dryWetVal;
    }

    void setDryWetPtr (std::atomic<flnum>* _dryWet)
    {
        dryWet = _dryWet;
        dryWetVal = *dryWet;
    }

    flnum getMaxDelayTime_msec() const override
    {
        return 25.0;
    }

    void parameterChanged()
    {
        chorusOnVal = *chorusOn;
        delayTime_msecVal = *delayTime_msec;
        feedbackVal = *feedback;
        depthVal = *depth;
        rateVal = *rate;
        dryWetVal = *dryWet;
    }

    std::vector<ParamMetaInfo> getParamMetaList()
    {
        constexpr int numDecimal = 4;
        return {
            { "chorusOn", "Chorus", 0.0, &chorusOn, ParamUtil::valueToOnOffString },
            { "chorusDelayTime", "Chorus Delay Time", 0.2572428286075592, &delayTime_msec, [numDecimal, this] (float value) {
                 return ParamUtil::valueToString (
                            convertNormalizedValToDelayTime_msec (value), numDecimal)
                        + " msec";
             } },
            { "chorusFeedback", "Chorus Feedback", 0.8885090947151184, &feedback, [numDecimal, this] (float value) {
                 return ParamUtil::valueToString (
                     convertNormalizedValToFeedback (value), numDecimal);
             } },
            { "chorusDepth", "Chorus Depth", 0.6134440302848816, &depth, [numDecimal, this] (float value) {
                 return ParamUtil::valueToString (
                     convertNormalizedValToDepth (value), numDecimal);
             } },
            { "chorusRate", "Chorus Rate", 0.5189887285232544, &rate, [numDecimal] (float value) { return ParamUtil::valueToString (lowestRateVal() * pow (rateBaseNumber(), value), 2) + " Hz"; } },
            { "chorusDryWet", "Chorus Dry/Wet", 0.5, &dryWet, [numDecimal] (float value) { return ParamUtil::valueToString (value, numDecimal); } }
        };
    }

private:
    std::atomic<flnum>* chorusOn {};
    std::atomic<flnum>* delayTime_msec {};
    std::atomic<flnum>* feedback {};
    std::atomic<flnum>* depth {};
    std::atomic<flnum>* rate {};
    std::atomic<flnum>* dryWet {};

    flnum chorusOnVal = 0.0;
    flnum delayTime_msecVal = 0.0;
    flnum feedbackVal = 0.0;
    flnum depthVal = 0.0;
    flnum rateVal = 0.0;
    flnum dryWetVal = 0.0;

    // Map flnum value [0, 1] to [0, 1]
    static constexpr flnum delayTimeCurve (flnum val0to1)
    {
        // return std::pow(val0to1, 1.0 / 10.0);
        return val0to1;
    }

    // Map flnum value [0, 1] to [0, 1]
    static constexpr flnum feedbackCurve (flnum val0to1)
    {
        // return std::pow(val0to1, 1.0 / 10.0);
        return val0to1;
    }

    // Map flnum value [0, 1] to [0, 1]
    static constexpr flnum depthCurve (flnum val0to1)
    {
        // return std::pow(val0to1, 1.0 / 10.0);
        return val0to1;
    }

    flnum convertNormalizedValToDelayTime_msec (flnum normalizedVal) const
    {
        // normalizedVal: [0.0, 1.0]
        constexpr flnum minDelaySize_msec = 0.0;
        return minDelaySize_msec + delayTimeCurve (normalizedVal) * (getMaxDelayTime_msec() - minDelaySize_msec);
    }

    flnum convertNormalizedValToFeedback (flnum normalizedVal) const
    {
        constexpr flnum minFeedback = 0.0;
        constexpr flnum maxFeedback = 0.8;
        return minFeedback + feedbackCurve (normalizedVal) * (maxFeedback - minFeedback);
    }

    flnum convertNormalizedValToDepth (flnum normalizedVal) const
    {
        constexpr flnum minDepth = 0.0;
        constexpr flnum maxDepth = 0.5;
        return minDepth + depthCurve (depthVal) * (maxDepth - minDepth);
    }

    // ---
    // Parameter converting consts
    // Rate
    static constexpr flnum lowestRateVal()
    {
        return 0.1; // [Hz]
    }

    static constexpr flnum rateBaseNumber()
    {
        return 500.0;
    }
};
} // namespace onsen
