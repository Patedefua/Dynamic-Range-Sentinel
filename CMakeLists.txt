cmake_minimum_required(VERSION 3.15)

project(DynamicRangeSentinel VERSION 1.0.0)

# JUCE
include(FetchContent)
FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(juce)

# === PLUGIN SETUP ===
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME "Patedefua"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    PLUGIN_MANUFACTURER_CODE PdFu
    PLUGIN_CODE DRS1
    FORMATS VST2
    PRODUCT_NAME "DynamicRangeSentinel"
)

# === FUENTES DEL PLUGIN ===
target_sources(DynamicRangeSentinel PRIVATE
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
)

# === HEADERS VST2 ===
target_compile_definitions(DynamicRangeSentinel PRIVATE JUCE_VST2_CAN_REPLACE_VST3=0)

# === LINK A JUCE ===
target_link_libraries(DynamicRangeSentinel PRIVATE
    juce::juce_audio_utils
    BinaryData
)

# === INCLUIR RECURSOS BINARIOS ===
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

# === VST2 SDK ===
if(WIN32)
    set(VST2_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/VST_SDK/VST2_SDK")
    if(EXISTS "${VST2_SDK_DIR}/pluginterfaces/vst2.x/aeffect.h")
        target_compile_definitions(DynamicRangeSentinel PRIVATE JUCE_VST2_HEADERS_INCLUDED)
        target_include_directories(DynamicRangeSentinel PRIVATE "${VST2_SDK_DIR}/pluginterfaces/vst2.x")
    else()
        message(FATAL_ERROR "VST2 SDK no encontrado. Colócalo en VST_SDK/VST2_SDK/pluginterfaces/vst2.x/")
    endif()
endif()
