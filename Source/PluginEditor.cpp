#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_extra/juce_gui_extra.h>


#if JUCE_BUILD_GUI

DynamicRangeSentinelEditor::DynamicRangeSentinelEditor (DynamicRangeSentinelProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);

    targetPeakKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    targetPeakKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(targetPeakKnob);
    targetPeakAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "TARGET_PEAK", targetPeakKnob);

    lookaheadSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    lookaheadSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(lookaheadSlider);
    lookaheadAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LOOKAHEAD", lookaheadSlider);

    setSize (700, 450);
}

DynamicRangeSentinelEditor::~DynamicRangeSentinelEditor() {}

void DynamicRangeSentinelEditor::paint (juce::Graphics& g)
{
    g.drawImage(backgroundImage, getLocalBounds().toFloat());
}

void DynamicRangeSentinelEditor::resized()
{
    targetPeakKnob.setBounds(95, 175, 150, 150);
    lookaheadSlider.setBounds(90, 395, 520, 25);
}

#endif // JUCE_BUILD_GUI
