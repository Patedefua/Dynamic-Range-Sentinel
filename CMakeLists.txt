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

target_link_libraries(DynamicRangeSentinel
  PRIVATE
    juce::juce_audio_utils
    BinaryData
)

# Para permitir VST2
target_compile_definitions(DynamicRangeSentinel
  PRIVATE
    JUCE_VST3_CAN_REPLACE_VST2=0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST2=1
)

# Incluir ruta al VST2 SDK para JUCE
target_include_directories(DynamicRangeSentinel
  PRIVATE "${VST2_SDK_PATH}"
)

# Configurar salida del plugin (.dll) para Windows
if (WIN32)
  set_target_properties(DynamicRangeSentinel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
    OUTPUT_NAME "DynamicRangeSentinel"
    SUFFIX ".dll"
  )
endif()

# Fuerza la salida del plugin como .dll y en la carpeta esperada
set_target_properties(DynamicRangeSentinel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
    OUTPUT_NAME "DynamicRangeSentinel"
)
