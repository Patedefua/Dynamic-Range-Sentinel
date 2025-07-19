#include "PluginProcessor.h"
#include "PluginEditor.h"

DynamicRangeSentinelProcessor::DynamicRangeSentinelProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    ), apvts(*this, nullptr, "Parameters", createParameterLayout())
#else
    : apvts(*this, nullptr, "Parameters", createParameterLayout())
#endif
{
    targetPeakParam = static_cast<std::atomic<float>*>(apvts.getRawParameterValue("TARGET_PEAK"));
    lookaheadParam = static_cast<std::atomic<float>*>(apvts.getRawParameterValue("LOOKAHEAD"));
}

DynamicRangeSentinelProcessor::~DynamicRangeSentinelProcessor() {}

const juce::String DynamicRangeSentinelProcessor::getName() const { return JucePlugin_Name; }

bool DynamicRangeSentinelProcessor::acceptsMidi() const { return false; }
bool DynamicRangeSentinelProcessor::producesMidi() const { return false; }
double DynamicRangeSentinelProcessor::getTailLengthSeconds() const { return 0.0; }
int DynamicRangeSentinelProcessor::getNumPrograms() { return 1; }
int DynamicRangeSentinelProcessor::getCurrentProgram() { return 0; }
void DynamicRangeSentinelProcessor::setCurrentProgram(int index) {}
const juce::String DynamicRangeSentinelProcessor::getProgramName(int index) { return {}; }
void DynamicRangeSentinelProcessor::changeProgramName(int index, const juce::String& newName) {}

void DynamicRangeSentinelProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    auto maxLookaheadSamples = static_cast<int>(std::ceil(sampleRate * 0.050));
    lookaheadBuffer.setSize(getTotalNumInputChannels(), maxLookaheadSamples);
    lookaheadBuffer.clear();
    writePosition = 0;
    smoothedGain = 1.0f;
}

void DynamicRangeSentinelProcessor::releaseResources()
{
    lookaheadBuffer.setSize(0, 0);
}

void DynamicRangeSentinelProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();
    auto targetPeak = targetPeakParam->load();
    auto lookaheadTimeMs = lookaheadParam->load();
    auto lookaheadSamples = static_cast<int>(lastSampleRate * lookaheadTimeMs / 1000.0);
    if (lookaheadSamples >= lookaheadBuffer.getNumSamples())
        lookaheadSamples = lookaheadBuffer.getNumSamples() - 1;

    for (int i = 0; i < numSamples; ++i)
    {
        for (int channel = 0; channel < totalNumInputChannels; ++channel)
        {
            const float* inputData = buffer.getReadPointer(channel);
            float* lookaheadData = lookaheadBuffer.getWritePointer(channel);
            lookaheadData[writePosition] = inputData[i];
        }

        float maxFuturePeak = 0.0f;
        for (int j = 0; j < lookaheadSamples; ++j)
        {
            int futurePosition = (writePosition + j) % lookaheadBuffer.getNumSamples();
            for (int channel = 0; channel < totalNumInputChannels; ++channel)
            {
                maxFuturePeak = std::max(maxFuturePeak, std::abs(lookaheadBuffer.getSample(channel, futurePosition)));
            }
        }

        float targetGain = 1.0f;
        if (maxFuturePeak > targetPeak)
        {
            targetGain = targetPeak / maxFuturePeak;
        }

        smoothedGain = smoothedGain * 0.99f + targetGain * 0.01f;

        int readPosition = (writePosition - lookaheadSamples + lookaheadBuffer.getNumSamples()) % lookaheadBuffer.getNumSamples();
        for (int channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            float sampleToProcess = lookaheadBuffer.getSample(channel, readPosition);
            float processedSample = sampleToProcess * smoothedGain;
            float* outputData = buffer.getWritePointer(channel);
            outputData[i] = processedSample;
        }
        writePosition = (writePosition + 1) % lookaheadBuffer.getNumSamples();
    }
}

juce::AudioProcessorEditor* DynamicRangeSentinelProcessor::createEditor()
{
    return new DynamicRangeSentinelEditor(*this);
}

bool DynamicRangeSentinelProcessor::hasEditor() const { return true; }

juce::AudioProcessorValueTreeState::ParameterLayout DynamicRangeSentinelProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat>("TARGET_PEAK", "Target Peak", 0.0f, 1.0f, 0.9f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LOOKAHEAD", "Lookahead", 1.0f, 50.0f, 20.0f));
    return { params.begin(), params.end() };
}

void DynamicRangeSentinelProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void DynamicRangeSentinelProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DynamicRangeSentinelProcessor();
}
