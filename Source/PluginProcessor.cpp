#include <JuceHeader.h>
#include "PluginProcessor.h"

DynamicRangeSentinelProcessor::DynamicRangeSentinelProcessor()
    : apvts(*this, nullptr, "Parameters", createParameterLayout())
{}

DynamicRangeSentinelProcessor::~DynamicRangeSentinelProcessor() {}

void DynamicRangeSentinelProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    lookaheadBuffer.setSize(getTotalNumInputChannels(), static_cast<int>(sampleRate * 2.0));
    lookaheadBuffer.clear();
    writePosition = 0;

    targetPeakParam = apvts.getRawParameterValue("TARGET_PEAK");
    lookaheadParam = apvts.getRawParameterValue("LOOKAHEAD");
}

void DynamicRangeSentinelProcessor::releaseResources() {}

void DynamicRangeSentinelProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto numSamples = buffer.getNumSamples();

    float targetPeak = *targetPeakParam;
    float lookaheadTime = *lookaheadParam;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < numSamples; ++sample)
        {
            float inputSample = channelData[sample];
            float gain = 1.0f;

            if (std::abs(inputSample) > targetPeak)
                gain = targetPeak / std::abs(inputSample);

            smoothedGain = 0.99f * smoothedGain + 0.01f * gain;
            channelData[sample] *= smoothedGain;
        }
    }
}

juce::AudioProcessorEditor* DynamicRangeSentinelProcessor::createEditor() {
    return new DynamicRangeSentinelEditor(*this);
}

bool DynamicRangeSentinelProcessor::hasEditor() const { return true; }
const juce::String DynamicRangeSentinelProcessor::getName() const { return "DynamicRangeSentinel"; }
bool DynamicRangeSentinelProcessor::acceptsMidi() const { return false; }
bool DynamicRangeSentinelProcessor::producesMidi() const { return false; }
double DynamicRangeSentinelProcessor::getTailLengthSeconds() const { return 0.0; }

int DynamicRangeSentinelProcessor::getNumPrograms() { return 1; }
int DynamicRangeSentinelProcessor::getCurrentProgram() { return 0; }
void DynamicRangeSentinelProcessor::setCurrentProgram(int) {}
const juce::String DynamicRangeSentinelProcessor::getProgramName(int) { return {}; }
void DynamicRangeSentinelProcessor::changeProgramName(int, const juce::String&) {}

void DynamicRangeSentinelProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    if (auto state = apvts.copyState())
        juce::MemoryOutputStream(destData, true).writeObject(state);
}

void DynamicRangeSentinelProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    if (auto state = juce::ValueTree::readFromData(data, static_cast<size_t>(sizeInBytes)))
        apvts.replaceState(state);
}

juce::AudioProcessorValueTreeState::ParameterLayout DynamicRangeSentinelProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("TARGET_PEAK", "Target Peak", 0.01f, 1.0f, 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LOOKAHEAD", "Lookahead", 0.0f, 0.2f, 0.02f));

    return { params.begin(), params.end() };
}
