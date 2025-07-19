cmake_minimum_required(VERSION 3.15)

project(DynamicRangeSentinel VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

# JUCE
include(FetchContent)
FetchContent_Declare(
  juce
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG origin/master
)
FetchContent_MakeAvailable(juce)

# Ruta al VST2 SDK (ADAPTADA A TU REPO)
set(VST2_SDK_PATH "${CMAKE_SOURCE_DIR}/vst2sdk/public.sdk/source/vst2.x")

if(NOT EXISTS "${VST2_SDK_PATH}/aeffect.h")
    message(FATAL_ERROR "VST2 SDK no encontrado en: ${VST2_SDK_PATH}")
endif()

# Agregar headers de VST2 al path
include_directories(${VST2_SDK_PATH})

# JUCE Plugin Setup
juce_enable_vst2()

juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME "Patedefua"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE

    PLUGIN_MANUFACTURER_CODE PdFa
    PLUGIN_CODE DrSe
    FORMATS VST2
    PRODUCT_NAME "DynamicRangeSentinel"

    SOURCES
        Source/PluginEditor.cpp
        Source/PluginEditor.h
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
)

# Binarios (recursos)
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

target_link_libraries(DynamicRangeSentinel PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_formats
    juce::juce_core
    juce::juce_data_structures
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    BinaryData
)

target_include_directories(DynamicRangeSentinel PRIVATE ${VST2_SDK_PATH})
