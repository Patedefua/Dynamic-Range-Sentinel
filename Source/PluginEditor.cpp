#include "PluginEditor.h"

DynamicRangeSentinelEditor::DynamicRangeSentinelEditor (DynamicRangeSentinelAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    setSize (backgroundImage.getWidth(), backgroundImage.getHeight());

    thresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "THRESHOLD", thresholdSlider);
    ceilingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "CEILING", ceilingSlider);

    addAndMakeVisible(thresholdSlider);
    thresholdSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    thresholdSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    addAndMakeVisible(ceilingSlider);
    ceilingSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    ceilingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
}

DynamicRangeSentinelEditor::~DynamicRangeSentinelEditor() = default;

void DynamicRangeSentinelEditor::paint (juce::Graphics& g)
{
    g.drawImageAt(backgroundImage, 0, 0);
}

void DynamicRangeSentinelEditor::resized()
{
    thresholdSlider.setBounds (50, 50, 100, 100);
    ceilingSlider.setBounds (250, 50, 100, 100);
}
