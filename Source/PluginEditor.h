#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class DynamicRangeSentinelEditor  : public juce::AudioProcessorEditor
{
public:
    explicit DynamicRangeSentinelEditor (DynamicRangeSentinelAudioProcessor&);
    ~DynamicRangeSentinelEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DynamicRangeSentinelAudioProcessor& processorRef;

    juce::Slider thresholdSlider, ceilingSlider;
    juce::Label thresholdLabel, ceilingLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicRangeSentinelEditor)
};
