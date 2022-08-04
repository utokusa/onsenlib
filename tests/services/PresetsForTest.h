#pragma once

#include <string>

// preset data from version 1.1.0
const std::string oldPresetVersion110 =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    ""
    "<Preset>"
    "  <Gadget>OnsenlibSynth</Gadget>"
    "  <SavedByVersion>1.1.0</SavedByVersion>"
    "  <Version>0</Version>"
    "  <State>"
    "    <OnsenlibSynth>"
    "      <PARAM id=\"attack\" value=\"0.0\"/>"
    "      <PARAM id=\"chorusOn\" value=\"0.0\"/>"
    "      <PARAM id=\"decay\" value=\"0.3199999630451202\"/>"
    "      <PARAM id=\"envForAmpOn\" value=\"0.0\"/>"
    "      <PARAM id=\"filterEnv\" value=\"0.9200000166893005\"/>"
    "      <PARAM id=\"frequency\" value=\"0.244999960064888\"/>"
    "      <PARAM id=\"hpfFreq\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoDelay\" value=\"0.5\"/>"
    "      <PARAM id=\"lfoFilterFreq\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoPhase\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoPitch\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoShape\" value=\"0.0\"/>"
    "      <PARAM id=\"masterFineTune\" value=\"0.5\"/>"
    "      <PARAM id=\"masterOctaveTune\" value=\"0.4000000059604645\"/>"
    "      <PARAM id=\"masterSemitoneTune\" value=\"0.5\"/>"
    "      <PARAM id=\"masterVolume\" value=\"0.7524999976158142\"/>"
    "      <PARAM id=\"noiseGain\" value=\"0.5\"/>"
    "      <PARAM id=\"numVoices\" value=\"0.0\"/>"
    "      <PARAM id=\"pitchBendWidth\" value=\"0.5\"/>"
    "      <PARAM id=\"portamento\" value=\"0.1000000089406967\"/>"
    "      <PARAM id=\"rate\" value=\"0.0\"/>"
    "      <PARAM id=\"rateSync\" value=\"0.0\"/>"
    "      <PARAM id=\"release\" value=\"0.5\"/>"
    "      <PARAM id=\"resonance\" value=\"0.3650000095367432\"/>"
    "      <PARAM id=\"sawGain\" value=\"0.0\"/>"
    "      <PARAM id=\"shape\" value=\"0.0\"/>"
    "      <PARAM id=\"sinGain\" value=\"1.0\"/>"
    "      <PARAM id=\"squareGain\" value=\"1.0\"/>"
    "      <PARAM id=\"subSquareGain\" value=\"1.0\"/>"
    "      <PARAM id=\"sustain\" value=\"0.2300000190734863\"/>"
    "      <PARAM id=\"syncOn\" value=\"0.0\"/>"
    "    </OnsenlibSynth>"
    "  </State>"
    "</Preset>";

// preset data with an invalid param (Or future version's parameter)
const std::string presetWithInvalidParam =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    ""
    "<Preset>"
    "  <Gadget>OnsenlibSynth</Gadget>"
    "  <SavedByVersion>13.1.0</SavedByVersion>"
    "  <Version>0</Version>"
    "  <State>"
    "    <OnsenlibSynth>"
    "      <PARAM id=\"attack\" value=\"0.0\"/>"
    "      <PARAM id=\"chorusOn\" value=\"0.0\"/>"
    "      <PARAM id=\"decay\" value=\"0.3199999630451202\"/>"
    "      <PARAM id=\"envForAmpOn\" value=\"0.0\"/>"
    "      <PARAM id=\"filterEnv\" value=\"0.9200000166893005\"/>"
    "      <PARAM id=\"frequency\" value=\"0.244999960064888\"/>"
    "      <PARAM id=\"hpfFreq\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoDelay\" value=\"0.5\"/>"
    "      <PARAM id=\"lfoFilterFreq\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoPhase\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoPitch\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoShape\" value=\"0.0\"/>"
    "      <PARAM id=\"masterFineTune\" value=\"0.5\"/>"
    "      <PARAM id=\"masterOctaveTune\" value=\"0.4000000059604645\"/>"
    "      <PARAM id=\"masterSemitoneTune\" value=\"0.5\"/>"
    "      <PARAM id=\"masterVolume\" value=\"0.7524999976158142\"/>"
    "      <PARAM id=\"noiseGain\" value=\"0.5\"/>"
    "      <PARAM id=\"numVoices\" value=\"0.0\"/>"
    "      <PARAM id=\"pitchBendWidth\" value=\"0.5\"/>"
    "      <PARAM id=\"portamento\" value=\"0.1000000089406967\"/>"
    "      <PARAM id=\"rate\" value=\"0.0\"/>"
    "      <PARAM id=\"rateSync\" value=\"0.0\"/>"
    "      <PARAM id=\"release\" value=\"0.5\"/>"
    "      <PARAM id=\"resonance\" value=\"0.3650000095367432\"/>"
    "      <PARAM id=\"sawGain\" value=\"0.0\"/>"
    "      <PARAM id=\"shape\" value=\"0.0\"/>"
    "      <PARAM id=\"sinGain\" value=\"1.0\"/>"
    "      <PARAM id=\"squareGain\" value=\"1.0\"/>"
    "      <PARAM id=\"subSquareGain\" value=\"1.0\"/>"
    "      <PARAM id=\"sustain\" value=\"0.2300000190734863\"/>"
    "      <PARAM id=\"syncOn\" value=\"0.0\"/>"
    "      <PARAM id=\"unisonOn\" value=\"0.0\"/>"
    "      <PARAM id=\"futureParam\" value=\"0.123\"/>"
    "    </OnsenlibSynth>"
    "  </State>"
    "</Preset>";

// preset data with an invalid param (invalid decay)
const std::string presetWithInvalidParamValue =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    ""
    "<Preset>"
    "  <Gadget>OnsenlibSynth</Gadget>"
    "  <SavedByVersion>13.1.0</SavedByVersion>"
    "  <Version>0</Version>"
    "  <State>"
    "    <OnsenlibSynth>"
    "      <PARAM id=\"attack\" value=\"0.0\"/>"
    "      <PARAM id=\"chorusOn\" value=\"0.0\"/>"
    "      <PARAM id=\"decay\" value=\"100.0\"/>"
    "      <PARAM id=\"envForAmpOn\" value=\"0.0\"/>"
    "      <PARAM id=\"filterEnv\" value=\"0.9200000166893005\"/>"
    "      <PARAM id=\"frequency\" value=\"0.244999960064888\"/>"
    "      <PARAM id=\"hpfFreq\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoDelay\" value=\"0.5\"/>"
    "      <PARAM id=\"lfoFilterFreq\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoPhase\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoPitch\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoShape\" value=\"0.0\"/>"
    "      <PARAM id=\"masterFineTune\" value=\"0.5\"/>"
    "      <PARAM id=\"masterOctaveTune\" value=\"0.4000000059604645\"/>"
    "      <PARAM id=\"masterSemitoneTune\" value=\"0.5\"/>"
    "      <PARAM id=\"masterVolume\" value=\"0.7524999976158142\"/>"
    "      <PARAM id=\"noiseGain\" value=\"0.5\"/>"
    "      <PARAM id=\"numVoices\" value=\"0.0\"/>"
    "      <PARAM id=\"pitchBendWidth\" value=\"0.5\"/>"
    "      <PARAM id=\"portamento\" value=\"0.1000000089406967\"/>"
    "      <PARAM id=\"rate\" value=\"0.0\"/>"
    "      <PARAM id=\"rateSync\" value=\"0.0\"/>"
    "      <PARAM id=\"release\" value=\"0.5\"/>"
    "      <PARAM id=\"resonance\" value=\"0.3650000095367432\"/>"
    "      <PARAM id=\"sawGain\" value=\"0.0\"/>"
    "      <PARAM id=\"shape\" value=\"0.0\"/>"
    "      <PARAM id=\"sinGain\" value=\"1.0\"/>"
    "      <PARAM id=\"squareGain\" value=\"1.0\"/>"
    "      <PARAM id=\"subSquareGain\" value=\"1.0\"/>"
    "      <PARAM id=\"sustain\" value=\"0.2300000190734863\"/>"
    "      <PARAM id=\"syncOn\" value=\"0.0\"/>"
    "      <PARAM id=\"unisonOn\" value=\"0.0\"/>"
    "      <PARAM id=\"futureParam\" value=\"0.123\"/>"
    "    </OnsenlibSynth>"
    "  </State>"
    "</Preset>";

// preset data with an invalid param (invalid decay)
const std::string presetWithInvalidParamValueType =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    ""
    "<Preset>"
    "  <Gadget>OnsenlibSynth</Gadget>"
    "  <SavedByVersion>13.1.0</SavedByVersion>"
    "  <Version>0</Version>"
    "  <State>"
    "    <OnsenlibSynth>"
    "      <PARAM id=\"attack\" value=\"0.0\"/>"
    "      <PARAM id=\"chorusOn\" value=\"0.0\"/>"
    "      <PARAM id=\"decay\" value=\"invalid\"/>"
    "      <PARAM id=\"envForAmpOn\" value=\"0.0\"/>"
    "      <PARAM id=\"filterEnv\" value=\"0.9200000166893005\"/>"
    "      <PARAM id=\"frequency\" value=\"0.244999960064888\"/>"
    "      <PARAM id=\"hpfFreq\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoDelay\" value=\"0.5\"/>"
    "      <PARAM id=\"lfoFilterFreq\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoPhase\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoPitch\" value=\"0.0\"/>"
    "      <PARAM id=\"lfoShape\" value=\"0.0\"/>"
    "      <PARAM id=\"masterFineTune\" value=\"0.5\"/>"
    "      <PARAM id=\"masterOctaveTune\" value=\"0.4000000059604645\"/>"
    "      <PARAM id=\"masterSemitoneTune\" value=\"0.5\"/>"
    "      <PARAM id=\"masterVolume\" value=\"0.7524999976158142\"/>"
    "      <PARAM id=\"noiseGain\" value=\"0.5\"/>"
    "      <PARAM id=\"numVoices\" value=\"0.0\"/>"
    "      <PARAM id=\"pitchBendWidth\" value=\"0.5\"/>"
    "      <PARAM id=\"portamento\" value=\"0.1000000089406967\"/>"
    "      <PARAM id=\"rate\" value=\"0.0\"/>"
    "      <PARAM id=\"rateSync\" value=\"0.0\"/>"
    "      <PARAM id=\"release\" value=\"0.5\"/>"
    "      <PARAM id=\"resonance\" value=\"0.3650000095367432\"/>"
    "      <PARAM id=\"sawGain\" value=\"0.0\"/>"
    "      <PARAM id=\"shape\" value=\"0.0\"/>"
    "      <PARAM id=\"sinGain\" value=\"1.0\"/>"
    "      <PARAM id=\"squareGain\" value=\"1.0\"/>"
    "      <PARAM id=\"subSquareGain\" value=\"1.0\"/>"
    "      <PARAM id=\"sustain\" value=\"0.2300000190734863\"/>"
    "      <PARAM id=\"syncOn\" value=\"0.0\"/>"
    "      <PARAM id=\"unisonOn\" value=\"0.0\"/>"
    "      <PARAM id=\"futureParam\" value=\"0.123\"/>"
    "    </OnsenlibSynth>"
    "  </State>"
    "</Preset>";