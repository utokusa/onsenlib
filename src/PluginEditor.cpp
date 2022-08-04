/*
  ==============================================================================

   JUCE Plugin Editor for reace-juce

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "services/TmpFileManager.h"
#include "views/ClippingIndicatorView.h"
#include "views/PresetManagerView.h"
#include <iostream>

//==============================================================================
OnsenlibSynthAudioProcessorEditor::OnsenlibSynthAudioProcessorEditor (OnsenlibSynthAudioProcessor& proc, juce::AudioProcessorValueTreeState&, onsen::PresetManager& _presetManager, onsen::ISynthUi* _synthUi)
    : juce::AudioProcessorEditor (&proc),
      audioProcessor (proc),
      presetManager (_presetManager),
      synthUi (_synthUi),
      engine (std::make_shared<reactjuce::EcmascriptEngine>()),
      appRoot (engine),
      harness (std::make_unique<reactjuce::AppHarness> (appRoot)),
      tmpUiBundlePath(),
      dirtyParamFlags ((processor.getParameters().size()))
{
    setUpParameters();
    harness->onBeforeAll = [this]() {
        beforeBundleEvaluated();
    };

    harness->onAfterAll = [this]() {
        afterBundleEvaluated();
    };

    harness->watch (getBundle());

#if JUCE_DEBUG
    harness->start();
#else
    harness->once();
#endif

    // Delete tmp file as soon as possible
    auto tmpUiBundle = juce::File (tmpUiBundlePath);
    tmpUiBundle.deleteFile();

    appRoot.setWantsKeyboardFocus (false);
    addAndMakeVisible (appRoot);

    setSize (appWidth, appHeight);
    startTimerHz (30);
}

OnsenlibSynthAudioProcessorEditor::~OnsenlibSynthAudioProcessorEditor()
{
    for (auto& param : audioProcessor.getParameters())
    {
        param->removeListener (this);
    }
};

//==============================================================================
void OnsenlibSynthAudioProcessorEditor::parameterValueChanged (int parameterIndex, float newValue)
{
    dirtyParamFlags[parameterIndex] = true;
}

void OnsenlibSynthAudioProcessorEditor::parameterGestureChanged (int, bool)
{
}

//==============================================================================
void OnsenlibSynthAudioProcessorEditor::timerCallback()
{
    updateUi();
}

//==============================================================================
void OnsenlibSynthAudioProcessorEditor::resized()
{
    appRoot.setBounds (getLocalBounds());
}

void OnsenlibSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::transparentWhite);
}

//==============================================================================
juce::File OnsenlibSynthAudioProcessorEditor::getBundle()
{
    const juce::File dir = onsen::TmpFileManager::getTmpDir();
    const juce::String jsFileName = "main.js";
    juce::File bundle = onsen::TmpFileManager::createTempFile (dir, jsFileName);
    tmpUiBundlePath = bundle.getFullPathName(); // It should be deleted on the caller

    {
        dir.createDirectory();
        juce::FileOutputStream fs = juce::FileOutputStream (bundle);
        fs.write (BinaryData::main_js, BinaryData::main_jsSize);
        fs.flush();
    }

#if JUCE_DEBUG
    juce::File sourceDir = juce::File (ONSENLIBSYNTH_SOURCE_DIR);
    bundle = sourceDir.getChildFile ("jsui/build/js/main.js");
#endif
    return bundle;
}

void OnsenlibSynthAudioProcessorEditor::setUpParameters()
{
    auto& processorParams = audioProcessor.getParameters();

    for (auto& param : processorParams)
    {
        auto paramWithId = dynamic_cast<juce::AudioProcessorParameterWithID*> (param);
        assert (paramWithId);
        parameterById[paramWithId->paramID] = param;
        dirtyParamFlags[param->getParameterIndex()] = true;
        param->addListener (this);
    }
}
void OnsenlibSynthAudioProcessorEditor::updateUi()
{
    for (int i = 0; i < dirtyParamFlags.size(); ++i)
    {
        if (dirtyParamFlags[i])
        {
            dirtyParamFlags[i] = false;

            const auto& param = audioProcessor.getParameters()[i];

            auto* paramWithId = dynamic_cast<juce::AudioProcessorParameterWithID*> (param);
            assert (paramWithId);
            juce::String paramId = paramWithId->paramID;

            float defaultValue = param->getDefaultValue();
            const float value = param->getValue();
            juce::String stringValue = param->getText (value, 0);

            appRoot.dispatchEvent (
                "parameterValueChange",
                i,
                paramId,
                defaultValue,
                value,
                stringValue);
        }
    }
}

void OnsenlibSynthAudioProcessorEditor::beforeBundleEvaluated()
{
    appRoot.registerViewType (
        "ClippingIndicatorView",
        [this]() -> reactjuce::ViewManager::ViewPair {
            auto view = std::make_unique<onsen::ClippingIndicatorView> (synthUi);
            auto shadowView = std::make_unique<reactjuce::ShadowView> (view.get());

            return { std::move (view), std::move (shadowView) };
        });

    appRoot.registerViewType (
        "PresetManagerView",
        [this]() -> reactjuce::ViewManager::ViewPair {
            auto view = std::make_unique<onsen::PresetManagerView> (presetManager);
            auto shadowView = std::make_unique<reactjuce::ShadowView> (view.get());

            return { std::move (view), std::move (shadowView) };
        });

    engine->registerNativeMethod (
        "beginParameterChangeGesture",
        [this] (const juce::var::NativeFunctionArgs& args) {
            auto paramId = args.arguments[0].toString();
            auto it = parameterById.find (paramId);
            if (it != parameterById.end())
                it->second->beginChangeGesture();

            return juce::var::undefined();
        });

    engine->registerNativeMethod (
        "setParameterValueNotifyingHost",
        [this] (const juce::var::NativeFunctionArgs& args) {
            auto paramId = args.arguments[0].toString();
            auto newValue = args.arguments[1];
            auto it = parameterById.find (paramId);
            if (it != parameterById.end())
                it->second->setValueNotifyingHost (newValue);

            return juce::var::undefined();
        });

    engine->registerNativeMethod (
        "endParameterChangeGesture",
        [this] (const juce::var::NativeFunctionArgs& args) {
            auto paramId = args.arguments[0].toString();
            auto it = parameterById.find (paramId);
            if (it != parameterById.end())
                it->second->endChangeGesture();

            return juce::var::undefined();
        });
}

void OnsenlibSynthAudioProcessorEditor::afterBundleEvaluated()
{
    for (auto& param : audioProcessor.getParameters())
    {
        parameterValueChanged (param->getParameterIndex(), param->getValue());
    }
}
