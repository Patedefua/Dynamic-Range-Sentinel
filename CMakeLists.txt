cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

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

juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST2
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
    PLUGIN_VST2_CATEGORY  "Dynamics"
)

# Añade los archivos de código fuente y los recursos directamente al plugin
target_sources(DynamicRangeSentinel PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

target_link_libraries(DynamicRangeSentinel PRIVATE BinaryData)
