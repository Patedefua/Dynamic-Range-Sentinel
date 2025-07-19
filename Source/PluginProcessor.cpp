#include "PluginProcessor.h"
#include "PluginEditor.h"

DynamicRangeSentinelAudioProcessor::DynamicRangeSentinelAudioProcessor()
     : AudioProcessor (BusesProperties().withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
       // ⚡ ARQUITECTURA MODERNA: Inicializamos el APVTS en el constructor.
       apvts (*this, nullptr, "Parameters", createParameterLayout())
{
}

DynamicRangeSentinelAudioProcessor::~DynamicRangeSentinelAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout DynamicRangeSentinelAudioProcessor::createParameterLayout()
{
    // ⚡ GESTIÓN DE PARÁMETROS CENTRALIZADA: Todos los parámetros se definen aquí.
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back (std::make_unique<juce::AudioParameterFloat> ("THRESHOLD", "Threshold", -60.0f, 0.0f, -12.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("CEILING", "Ceiling", -60.0f, 0.0f, -0.1f));

    return { params.begin(), params.end() };
}

void DynamicRangeSentinelAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // ⚡ PREPARACIÓN DEL DSP: Configuramos el limitador con las especificaciones de la sesión.
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    limiter.prepare(spec);
    limiter.setRelease(100.0f); // Release de 100ms
}

void DynamicRangeSentinelAudioProcessor::releaseResources() {}

void DynamicRangeSentinelAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    // ⚡ LÓGICA DE AUDIO REAL: Obtenemos los valores de los parámetros y los aplicamos al DSP.
    auto thresholdValue = apvts.getRawParameterValue("THRESHOLD")->load();
    auto ceilingValue = apvts.getRawParameterValue("CEILING")->load();
    
    // El limitador de JUCE usa el "threshold" para la reducción y no tiene un "ceiling" separado.
    // Usaremos el Threshold para el limitador y luego aplicaremos un clipper en el Ceiling si es necesario,
    // o simplemente usamos el Threshold como el punto de limitación.
    // Para este prototipo, el Threshold del limitador será nuestro control principal.
    limiter.setThreshold(thresholdValue);

    // Envolvemos el buffer para que el DSP de JUCE pueda usarlo.
    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);
    limiter.process(context);

    // Aquí podríamos añadir un clipper final usando 'ceilingValue' si quisiéramos un control separado.
}


void DynamicRangeSentinelAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // ⚡ GESTIÓN DE ESTADO AUTOMATIZADA: APVTS se encarga de todo.
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void DynamicRangeSentinelAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

juce::AudioProcessorEditor* DynamicRangeSentinelAudioProcessor::createEditor()
{
    return new DynamicRangeSentinelEditor (*this);
}

// --- El resto del código boilerplate permanece igual ---
const juce::String DynamicRangeSentinelAudioProcessor::getName() const { return "DynamicRangeSentinel"; }
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
