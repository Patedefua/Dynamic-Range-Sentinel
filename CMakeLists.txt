cmake_minimum_required(VERSION 3.15)

project(DynamicRangeSentinel VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

# JUCE path (ajustar si es submódulo o carpeta externa)
set(JUCE_DIR "${CMAKE_SOURCE_DIR}/JUCE")

# Plugin format
set(BUILD_VST2 TRUE)

# Ruta VST2 SDK
set(VST2_SDK_PATH "${CMAKE_SOURCE_DIR}/vst2sdk")

# Agregar JUCE
add_subdirectory(${JUCE_DIR} JUCE)

# Agregar binarios/recursos
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

# Agregar plugin
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME "Patedefua"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE

    PLUGIN_MANUFACTURER_CODE PdF0
    PLUGIN_CODE DRS0
    FORMATS VST2
    PRODUCT_NAME "DynamicRangeSentinel"
)

# Archivos fuente
target_sources(DynamicRangeSentinel PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

# Includes para VST2 SDK
target_include_directories(DynamicRangeSentinel PRIVATE
    "${VST2_SDK_PATH}"
)

# Definiciones para VST2
target_compile_definitions(DynamicRangeSentinel PRIVATE
    JUCE_VST2_HEADERS_INCLUDED=1
)

# Vinculación con JUCE y recursos binarios
target_link_libraries(DynamicRangeSentinel PRIVATE
    BinaryData
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_basics
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_dsp
)
