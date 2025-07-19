#include "PluginProcessor.h"
#include "public.sdk/source/vst2.x/aeffect.h"
#include "public.sdk/source/vst2.x/aeffectx.h"

extern "C" __declspec(dllexport) AEffect* VSTPluginMain(audioMasterCallback audioMaster)
{
    if (!audioMaster)
        return nullptr;

    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    return juce::createPluginFilterOfType(juce::AudioProcessor::WrapperType::wrapperType_VST)
        ->getAEffectHandle(audioMaster);
}

// VSTPluginMain is sometimes aliased to main
extern "C" __declspec(dllexport) AEffect* main(audioMasterCallback audioMaster)
{
    return VSTPluginMain(audioMaster);
}
