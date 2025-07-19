// ruta: Source/PluginEditor.cpp
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
DynamicRangeSentinelEditor::DynamicRangeSentinelEditor (DynamicRangeSentinelAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    // Carga la imagen de fondo desde los datos binarios
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);

    // Configura el tamaño de la ventana del editor basado en la imagen de fondo
    setSize (backgroundImage.getWidth(), backgroundImage.getHeight());
}

DynamicRangeSentinelEditor::~DynamicRangeSentinelEditor()
{
}

//==============================================================================
void DynamicRangeSentinelEditor::paint (juce::Graphics& g)
{
    // Dibuja la imagen de fondo
    g.drawImageAt(backgroundImage, 0, 0);
}

void DynamicRangeSentinelEditor::resized()
{
    // Aquí es donde posicionarías tus sliders y otros controles en el futuro.
    // Por ahora, lo dejamos vacío.
}
