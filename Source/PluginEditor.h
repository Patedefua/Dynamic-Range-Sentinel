#pragma once

#include "PluginProcessor.h"

#if JUCE_BUILD_GUI

class DynamicRangeSentinelEditor  : public juce::AudioProcessorEditor
{
public:
    DynamicRangeSentinelEditor (DynamicRangeSentinelProcessor&);
    ~DynamicRangeSentinelEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DynamicRangeSentinelProcessor& audioProcessor;

    juce::Image backgroundImage;
    juce::Slider targetPeakKnob;
    juce::Slider lookaheadSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> targetPeakAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lookaheadAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicRangeSentinelEditor)
};

#endif // JUCE_BUILD_GUI
