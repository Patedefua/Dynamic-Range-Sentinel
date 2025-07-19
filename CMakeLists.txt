cmake_minimum_required(VERSION 3.15)

# Detectar plataforma correctamente con comillas
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(TARGET_PLATFORM_WINDOWS TRUE)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(TARGET_PLATFORM_MAC TRUE)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(TARGET_PLATFORM_LINUX TRUE)
endif()

# ⚠️ Sin OBJCXX para evitar errores en Linux
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
  JUCE
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG 7.0.11
)
FetchContent_MakeAvailable(JUCE)

option(BUILD_VST2_PLUGIN "Build VST2 plugin" ON)

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
  JucePlugin_VersionString="1.0.1"
)

# GUI condicional
if(TARGET_PLATFORM_LINUX)
    message(STATUS "🔧 Linux detected: building without GUI.")
    set(JUCE_GUI_MODULES juce_audio_processors)
else()
    message(STATUS "💻 GUI enabled (macOS or Windows).")
    set(JUCE_GUI_MODULES
        juce_audio_utils
        juce_gui_extra
    )
endif()

add_library(SharedCode STATIC
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_include_directories(SharedCode PRIVATE
    Source
)

target_link_libraries(SharedCode
    PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    ${JUCE_GUI_MODULES}
)

if(BUILD_VST2_PLUGIN)
    juce_add_plugin(DynamicRangeSentinel
        COMPANY_NAME "Patedefua"
        PLUGIN_NAME "DynamicRangeSentinel"
        PLUGIN_MANUFACTURER_CODE PdFs
        PLUGIN_CODE DrSe
        FORMATS VST2
        PRODUCT_NAME "DynamicRangeSentinel"
        COPY_PLUGIN_AFTER_BUILD TRUE
    )

    target_sources(DynamicRangeSentinel PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
    )

    target_link_libraries(DynamicRangeSentinel PRIVATE SharedCode)
endif()
