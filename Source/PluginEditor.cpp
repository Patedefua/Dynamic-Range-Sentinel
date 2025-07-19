#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

DynamicRangeSentinelEditor::DynamicRangeSentinelEditor (DynamicRangeSentinelAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    // ⚡ INTEGRACIÓN GRÁFICA: Cargamos y usamos la imagen de fondo.
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    setSize (backgroundImage.getWidth(), backgroundImage.getHeight());

    // ⚡ CONEXIÓN AUTOMATIZADA: Creamos los attachments que vinculan la UI con los parámetros del APVTS.
    thresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "THRESHOLD", thresholdSlider);
    ceilingAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "CEILING", ceilingSlider);

    // --- Configuración visual de los sliders (puedes reemplazar esto con tus perillas personalizadas) ---
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
    // Dibuja la imagen de fondo.
    g.drawImageAt(backgroundImage, 0, 0);
}

void DynamicRangeSentinelEditor::resized()
{
    // Aquí posicionas tus sliders sobre la imagen de fondo.
    // Estos valores son ejemplos, ajústalos a tu diseño.
    thresholdSlider.setBounds (50, 50, 100, 100);
    ceilingSlider.setBounds (250, 50, 100, 100);
}
