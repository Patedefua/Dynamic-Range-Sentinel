cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

set(BUILD_WITH_GUI ON)

add_library(SharedCode STATIC
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

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

target_link_libraries(SharedCode PRIVATE
    juce::juce_audio_processors
    juce::juce_gui_extra
    juce::juce_audio_utils
    BinaryData
)

juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME "OpusNexus"
    PLUGIN_MANUFACTURER_CODE OpNx
    PLUGIN_CODE DRS1
    FORMATS VST2
    PRODUCT_NAME "DynamicRangeSentinel"
    BUNDLE_ID com.opusnexus.DynamicRangeSentinel
    VST2_CATEGORY Dynamics
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_OUTPUT_NAME "DynamicRangeSentinel"
)

target_link_libraries(DynamicRangeSentinel PRIVATE SharedCode)

add_compile_definitions(
    'JucePlugin_Manufacturer="Patedefua"'
    'JucePlugin_Name="DynamicRangeSentinel"'
)
