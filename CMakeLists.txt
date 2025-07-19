cmake_minimum_required(VERSION 3.15)

project(DynamicRangeSentinel VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JUCE
include(FetchContent)
FetchContent_Declare(
  juce
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG origin/master
)
FetchContent_MakeAvailable(juce)

# Ruta al SDK VST2
set(VST2_SDK_PATH "${CMAKE_SOURCE_DIR}/vst2sdk/public.sdk/source/vst2.x")

# Plugin
juce_add_plugin(DynamicRangeSentinel
  COMPANY_NAME "Patedefua"
  PLUGIN_NAME "Dynamic Range Sentinel"
  PLUGIN_MANUFACTURER_CODE PdFa
  PLUGIN_CODE DRS1
  FORMATS VST2
  PRODUCT_NAME "Dynamic Range Sentinel"
  COPY_PLUGIN_AFTER_BUILD TRUE
  PLUGIN_GUI TRUE
  SOURCE_FILES
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
)

# Recursos gráficos y fuentes
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

# Módulos y binarios

target_link_libraries(DynamicRangeSentinel
  PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    BinaryData
)

# Para permitir VST2

target_compile_definitions(DynamicRangeSentinel
  PRIVATE
    JUCE_VST3_CAN_REPLACE_VST2=0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST2=1
)

# Incluir ruta al VST2 SDK para JUCE y al source de JUCE

target_include_directories(DynamicRangeSentinel
  PRIVATE
    "${JUCE_SOURCE_DIR}"
    "${JUCE_SOURCE_DIR}/modules"
    "${VST2_SDK_PATH}"
)

# Definiciones adicionales de JUCE

target_compile_definitions(DynamicRangeSentinel
  PRIVATE
    JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:DynamicRangeSentinel,JUCE_PRODUCT_NAME>"
    JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:DynamicRangeSentinel,JUCE_VERSION>"
)
