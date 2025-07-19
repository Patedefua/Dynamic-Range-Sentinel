cmake_minimum_required(VERSION 3.15)

project(DynamicRangeSentinel VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JUCE vía FetchContent
include(FetchContent)
FetchContent_Declare(
  juce
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG master
)
FetchContent_MakeAvailable(juce)

# Ruta al SDK VST2 (asegúrate de que aeffect.h esté aquí)
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
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/VSTMain.cpp
)

# Recursos gráficos y fuentes (se generan como BinaryData)
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

# Incluir rutas necesarias
target_include_directories(DynamicRangeSentinel
  PRIVATE
    "${VST2_SDK_PATH}"
)

# Linkear librerías necesarias
target_link_libraries(DynamicRangeSentinel
  PRIVATE
    juce::juce_audio_utils
    BinaryData
)

# Definiciones necesarias para JUCE + VST2
target_compile_definitions(DynamicRangeSentinel
  PRIVATE
    JUCE_VST3_CAN_REPLACE_VST2=0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST2=1
)
