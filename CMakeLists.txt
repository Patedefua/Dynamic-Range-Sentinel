cmake_minimum_required(VERSION 3.15)

project(DynamicRangeSentinel VERSION 1.0.0)

# JUCE wrapper
include(FetchContent)

FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.9
)

FetchContent_MakeAvailable(juce)

# Activar VST2 usando ruta personalizada
set(JUCE_VST2SDK_LOCATION "${CMAKE_SOURCE_DIR}/vst2sdk/public.sdk")

juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME "Patedefua"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE PdF0
    PLUGIN_CODE Drs0
    FORMATS VST2
    PRODUCT_NAME "Dynamic Range Sentinel"
)

target_sources(DynamicRangeSentinel
    PRIVATE
        Source/PluginEditor.cpp
        Source/PluginProcessor.cpp
)

target_include_directories(DynamicRangeSentinel
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

# Binary resources (imágenes, fuentes, etc.)
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

target_link_libraries(DynamicRangeSentinel
    PRIVATE
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_gui_basics
        juce::juce_gui_extra
        BinaryData
)

# Exportar como DLL (VST2)
set_target_properties(DynamicRangeSentinel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
)
