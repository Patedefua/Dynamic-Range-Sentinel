#include "PluginEditor.h"

DynamicRangeSentinelEditor::DynamicRangeSentinelEditor (DynamicRangeSentinelAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setSize (400, 200);

    thresholdSlider.setSliderStyle (juce::Slider::LinearVertical);
    thresholdSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    thresholdSlider.setRange (-60.0f, 0.0f);
    thresholdSlider.setValue (*p.thresholdParam);
    thresholdSlider.onValueChange = [this] {
        processorRef.thresholdParam->setValueNotifyingHost ((float) thresholdSlider.getValue());
    };
    addAndMakeVisible (thresholdSlider);
    thresholdLabel.setText ("Threshold", juce::dontSendNotification);
    addAndMakeVisible (thresholdLabel);

    ceilingSlider.setSliderStyle (juce::Slider::LinearVertical);
    ceilingSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    ceilingSlider.setRange (-60.0f, 0.0f);
    ceilingSlider.setValue (*p.ceilingParam);
    ceilingSlider.onValueChange = [this] {
        processorRef.ceilingParam->setValueNotifyingHost ((float) ceilingSlider.getValue());
    };
    addAndMakeVisible (ceilingSlider);
    ceilingLabel.setText ("Ceiling", juce::dontSendNotification);
    addAndMakeVisible (ceilingLabel);
}

DynamicRangeSentinelEditor::~DynamicRangeSentinelEditor() = default;

void DynamicRangeSentinelEditor::paint (juce::Graphics& g) {
    g.fillAll (juce::Colours::black);
}

void DynamicRangeSentinelEditor::resized() {
    thresholdSlider.setBounds (50, 30, 120, 150);
    thresholdLabel.setBounds (50, 10, 120, 20);
    ceilingSlider.setBounds (230, 30, 120, 150);
    ceilingLabel.setBounds (230, 10, 120, 20);
}
