#pragma once

#include "PluginProcessor.h"
#include "BinaryData.h"

class DynamicRangeSentinelEditor  : public juce::AudioProcessorEditor
{
public:
    explicit DynamicRangeSentinelEditor (DynamicRangeSentinelAudioProcessor&);
    ~DynamicRangeSentinelEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DynamicRangeSentinelAudioProcessor& processorRef;
    juce::Image backgroundImage;
    juce::Slider thresholdSlider, ceilingSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ceilingAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicRangeSentinelEditor)
};
