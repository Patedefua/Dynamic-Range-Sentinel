cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX)

include(FetchContent)

# --- JUCE Framework fetch ---
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

# --- Asegurar que solo compila en Windows ---
if(NOT WIN32)
    message(FATAL_ERROR "Este plugin está configurado solo para Windows.")
endif()

# --- Plugin fuente compartida ---
add_library(SharedCode STATIC)
target_sources(SharedCode PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

juce_add_binary_data(BinaryData
    SOURCES
        Source/Resources/background.png
        Source/Resources/Sarpanch-Regular.ttf
)

target_link_libraries(SharedCode PRIVATE BinaryData)

# --- Plugin Target (VST2 .dll real) ---
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME "OpusNexus"
    PLUGIN_MANUFACTURER_CODE OpNx
    PLUGIN_CODE DRS1
    FORMATS VST2
    PRODUCT_NAME "DynamicRangeSentinel"
    BUNDLE_ID com.opusnexus.DynamicRangeSentinel
    VST2_CATEGORY Dynamics
)

target_link_libraries(DynamicRangeSentinel PRIVATE
    SharedCode
    juce::juce_audio_utils
)

# --- Correctas definiciones para que no fallen macros ---
add_compile_definitions(
    JucePlugin_Manufacturer="\"Patedefua\""
    JucePlugin_Name="\"DynamicRangeSentinel\""
)
