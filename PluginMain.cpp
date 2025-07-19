#include "PluginProcessor.h"

// Esta función se compila dentro del target del plugin (no en SharedCode)
const juce::String DynamicRangeSentinelProcessor::getName() const {
    return JucePlugin_Name;
}
