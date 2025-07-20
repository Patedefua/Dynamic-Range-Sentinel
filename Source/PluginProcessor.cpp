#include "PluginProcessor.h"
#include "PluginEditor.h"

DynamicRangeSentinelAudioProcessor::DynamicRangeSentinelAudioProcessor()
     : AudioProcessor (BusesProperties().withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
       apvts (*this, nullptr, "Parameters", createParameterLayout())
{
}

DynamicRangeSentinelAudioProcessor::~DynamicRangeSentinelAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout DynamicRangeSentinelAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("THRESHOLD", "Threshold", -60.0f, 0.0f, -12.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("CEILING", "Ceiling", -60.0f, 0.0f, -0.1f));
    return { params.begin(), params.end() };
}

void DynamicRangeSentinelAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    limiter.prepare(spec);
    limiter.setRelease(100.0f);
}

void DynamicRangeSentinelAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto thresholdValue = apvts.getRawParameterValue("THRESHOLD")->load();
    limiter.setThreshold(thresholdValue);

    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    limiter.process(context);
}

juce::AudioProcessorEditor* DynamicRangeSentinelAudioProcessor::createEditor() { return new DynamicRangeSentinelEditor (*this); }
const juce::String DynamicRangeSentinelAudioProcessor::getName() const { return "DynamicRangeSentinel"; }
void DynamicRangeSentinelAudioProcessor::releaseResources() {}
bool DynamicRangeSentinelAudioProcessor::hasEditor() const { return true; }
bool DynamicRangeSentinelAudioProcessor::acceptsMidi() const { return false; }
bool DynamicRangeSentinelAudioProcessor::producesMidi() const { return false; }
bool DynamicRangeSentinelAudioProcessor::isMidiEffect() const { return false; }
double DynamicRangeSentinelAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int DynamicRangeSentinelAudioProcessor::getNumPrograms() { return 1; }
int DynamicRangeSentinelAudioProcessor::getCurrentProgram() { return 0; }
void DynamicRangeSentinelAudioProcessor::setCurrentProgram (int) {}
const juce::String DynamicRangeSentinelAudioProcessor::getProgramName (int) { return {}; }
void DynamicRangeSentinelAudioProcessor::changeProgramName (int, const juce::String&) {}
bool DynamicRangeSentinelAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
void DynamicRangeSentinelAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}
void DynamicRangeSentinelAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}
