cmake_minimum_required(VERSION 3.22)

# Detect platform and set OBJCXX only for macOS
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C OBJCXX)
else()
    project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set plugin details using escaped quotes
add_compile_definitions(
    JucePlugin_Manufacturer="\"Patedefua\""
    JucePlugin_Name="\"DynamicRangeSentinel\""
)

# JUCE setup
add_subdirectory(JUCE)

# Include source files
file(GLOB_RECURSE SOURCE_FILES
    Source/*.cpp
    Source/*.h
)

# BinaryData setup (images, resources)
juce_add_binary_data(BinaryData SOURCES Assets/background.png)

# Create shared code library
add_library(SharedCode STATIC ${SOURCE_FILES})
target_link_libraries(SharedCode
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
        BinaryData
)

# Platform-specific plugin targets
if(CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # Plugin with GUI
    juce_add_plugin(DynamicRangeSentinel
        COMPANY_NAME "Patedefua"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT FALSE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE PdFu
        PLUGIN_CODE Drs1
        FORMATS VST3 AU
        PRODUCT_NAME "DynamicRangeSentinel"
    )
    target_link_libraries(DynamicRangeSentinel
        PRIVATE SharedCode
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Headless Linux build: no GUI, no plugin wrapper
    add_executable(DynamicRangeSentinelCLI Source/PluginProcessor.cpp)
    target_link_libraries(DynamicRangeSentinelCLI
        PRIVATE SharedCode
    )
endif()

# Recursos embebidos
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

target_link_libraries(SharedCode INTERFACE BinaryData)

# Crear plugin VST2 exclusivamente
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST2
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
    PLUGIN_VST2_CATEGORY  "Dynamics"
    NEEDS_MIDI_INPUT      False
    PRODUCES_MIDI_OUTPUT  False
    IS_SYNTH              False
    EDITOR_WANTS_KEYBOARD_FOCUS False
    COPY_PLUGIN_AFTER_BUILD TRUE
)

# Enlazar biblioteca compartida con el plugin
if(TARGET DynamicRangeSentinel_VST2)
    target_link_libraries(DynamicRangeSentinel_VST2 PRIVATE SharedCode)
endif()
