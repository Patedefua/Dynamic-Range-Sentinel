cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C OBJCXX)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

# PASO 1: Aislar nuestro código fuente.
add_library(SharedCode INTERFACE)
target_sources(SharedCode INTERFACE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

# PASO 2: Aislar nuestros recursos.
juce_add_binary_data(BinaryData
    SOURCES
        # ... (Lista de 17 archivos verificada) ...
)

# ⚡ EL PUENTE FINAL Y DECISIVO:
# Hacemos que los 'include paths' de BinaryData sean visibles para SharedCode.
target_link_libraries(SharedCode INTERFACE BinaryData)

# PASO 3: Invocar a juce_add_plugin en su forma más simple.
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST3 AU # VST2 omitido por obsolescencia y para simplificar.
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
)

# PASO 4: Enlace explícito y sintácticamente puro.
set(PLUGIN_TARGETS "")
if(TARGET DynamicRangeSentinel_VST3)
    list(APPEND PLUGIN_TARGETS DynamicRangeSentinel_VST3)
endif()
if(TARGET DynamicRangeSentinel_AU)
    list(APPEND PLUGIN_TARGETS DynamicRangeSentinel_AU)
endif()
if(TARGET DynamicRangeSentinel_VST2)
    list(APPEND PLUGIN_TARGETS DynamicRangeSentinel_VST2)
endif()

foreach(PLUGIN_TARGET ${PLUGIN_TARGETS})
    target_link_libraries(${PLUGIN_TARGET} PRIVATE SharedCode)
endforeach()
