cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

# Definiciones necesarias para evitar errores de compilación
add_compile_definitions(
  JucePlugin_Name="\"DynamicRangeSentinel\""
  JucePlugin_Manufacturer="\"Patedefua\""
  JucePlugin_ManufacturerCode=PdFs
  JucePlugin_PluginCode=DrSe
  JucePlugin_IsSynth=0
  JucePlugin_WantsMidiInput=0
  JucePlugin_ProducesMidiOutput=0
  JucePlugin_IsMidiEffect=0
  JucePlugin_EditorRequiresKeyboardFocus=0
  JucePlugin_Version=1.0.1
  JucePlugin_VersionCode=0x10001
  JucePlugin_VersionString="\"1.0.1\""
)

# Detectar plataforma
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(ENABLE_GUI TRUE)
elif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(ENABLE_GUI TRUE)
else()
    set(ENABLE_GUI FALSE)
endif()

add_library(SharedCode STATIC
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
)

if(ENABLE_GUI)
    target_sources(SharedCode PRIVATE
        Source/PluginEditor.cpp
        Source/PluginEditor.h
    )
endif()

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

target_link_libraries(SharedCode PRIVATE BinaryData)

juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME "OpusNexus"
    FORMATS VST2
    BUNDLE_ID com.opusnexus.DynamicRangeSentinel
    PLUGIN_MANUFACTURER_CODE PdFs
    PLUGIN_CODE DrSe
    PRODUCT_NAME "DynamicRangeSentinel"
)

if(ENABLE_GUI)
    target_link_libraries(DynamicRangeSentinel PRIVATE juce::juce_gui_basics juce::juce_gui_extra)
endif()

target_link_libraries(DynamicRangeSentinel PRIVATE SharedCode)
