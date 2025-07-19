#include "PluginProcessor.h"
#include "PluginEditor.h"

DynamicRangeSentinelAudioProcessor::DynamicRangeSentinelAudioProcessor()
    : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
    addParameter (thresholdParam = new juce::AudioParameterFloat ("threshold", "Threshold", -60.0f, 0.0f, -24.0f));
    addParameter (ceilingParam = new juce::AudioParameterFloat ("ceiling", "Ceiling", -60.0f, 0.0f, -1.0f));
}

DynamicRangeSentinelAudioProcessor::~DynamicRangeSentinelAudioProcessor() {}

const juce::String DynamicRangeSentinelAudioProcessor::getName() const {
    return "DynamicRangeSentinel";
}

bool DynamicRangeSentinelAudioProcessor::acceptsMidi() const { return false; }
bool DynamicRangeSentinelAudioProcessor::producesMidi() const { return false; }
bool DynamicRangeSentinelAudioProcessor::isMidiEffect() const { return false; }
double DynamicRangeSentinelAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int DynamicRangeSentinelAudioProcessor::getNumPrograms() { return 1; }
int DynamicRangeSentinelAudioProcessor::getCurrentProgram() { return 0; }
void DynamicRangeSentinelAudioProcessor::setCurrentProgram (int) {}
const juce::String DynamicRangeSentinelAudioProcessor::getProgramName (int) { return {}; }
void DynamicRangeSentinelAudioProcessor::changeProgramName (int, const juce::String&) {}

void DynamicRangeSentinelAudioProcessor::prepareToPlay (double, int) {}
void DynamicRangeSentinelAudioProcessor::releaseResources() {}

bool DynamicRangeSentinelAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
        && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void DynamicRangeSentinelAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    auto numChannels = getTotalNumInputChannels();
    auto numSamples = buffer.getNumSamples();

    for (int ch = 0; ch < numChannels; ++ch) {
        auto* data = buffer.getWritePointer (ch);
        for (int i = 0; i < numSamples; ++i) {
            float ceiling = juce::Decibels::decibelsToGain (*ceilingParam);
            data[i] = juce::jlimit (-ceiling, ceiling, data[i]);
        }
    }
}

bool DynamicRangeSentinelAudioProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor* DynamicRangeSentinelAudioProcessor::createEditor() {
    return new DynamicRangeSentinelEditor (*this);
}

void DynamicRangeSentinelAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    juce::MemoryOutputStream stream (destData, false);
    stream.writeFloat (*thresholdParam);
    stream.writeFloat (*ceilingParam);
}

void DynamicRangeSentinelAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    juce::MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);
    thresholdParam->setValueNotifyingHost (stream.readFloat());
    ceilingParam->setValueNotifyingHost (stream.readFloat());
}
