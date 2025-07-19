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
    
    // ⚡ INTEGRACIÓN GRÁFICA: Variable para guardar la imagen de fondo.
    juce::Image backgroundImage;

    juce::Slider thresholdSlider, ceilingSlider;
    juce::Label thresholdLabel, ceilingLabel;

    // ⚡ CONEXIÓN AUTOMATIZADA: Los "attachments" conectan los sliders a los parámetros automáticamente.
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ceilingAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicRangeSentinelEditor)
};
