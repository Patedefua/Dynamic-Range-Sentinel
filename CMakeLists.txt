cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C OBJCXX)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

# Define plugin metadata (corregido con comillas simples para escapar dobles)
add_compile_definitions(
    JucePlugin_Name='"DynamicRangeSentinel"'
    JucePlugin_Manufacturer='"Patedefua"'
    JucePlugin_PluginCode=DRSN
    JucePlugin_IsSynth=0
    JucePlugin_ProducesMidiOutput=0
    JucePlugin_WantsMidiInput=0
    JucePlugin_EditorRequiresKeyboardFocus=0
)

# Control de GUI por plataforma
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(JUCE_BUILD_GUI 0)
else()
    set(JUCE_BUILD_GUI 1)
endif()

# Crear biblioteca compartida de código fuente
add_library(SharedCode INTERFACE)
target_sources(SharedCode INTERFACE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
)

# Solo incluir PluginEditor si la GUI está habilitada
if(JUCE_BUILD_GUI)
    target_sources(SharedCode INTERFACE
        Source/PluginEditor.cpp
        Source/PluginEditor.h
    )
endif()

# Recursos embebidos
juce_add_binary_data(BinaryData
    SOURCES
        Source/Resources/background.png
        Source/Resources/circular_grille.png
        Source/Resources/gain_reduction_frame.png
        Source/Resources/gain_reduction_led.png
        Source/Resources/hires_logo.png
        Source/Resources/knob.png
        Source/Resources/logo_plate.png
        Source/Resources/quality_selector_knob.png
        Source/Resources/slider_handle.png
        Source/Resources/slider_track.png
        Source/Resources/switch_off.png
        Source/Resources/switch_on.png
        Source/Resources/vu_meter_background.png
        Source/Resources/vu_meter_background_peak.png
        Source/Resources/vu_meter_needle.png
        Source/Resources/waveform_graphic.png
        Source/Resources/Sarpanch-Regular.ttf
)

target_link_libraries(SharedCode INTERFACE BinaryData)

# Crear plugin VST2 exclusivamente
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST2
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
    PLUGIN_VST2_CATEGORY  "Dynamics"
    NEEDS_MIDI_INPUT      False
    PRODUCES_MIDI_OUTPUT  False
    IS_SYNTH              False
    EDITOR_WANTS_KEYBOARD_FOCUS False
    COPY_PLUGIN_AFTER_BUILD TRUE
)

# Enlazar biblioteca compartida con el plugin
if(TARGET DynamicRangeSentinel_VST2)
    target_link_libraries(DynamicRangeSentinel_VST2 PRIVATE SharedCode)
endif()
