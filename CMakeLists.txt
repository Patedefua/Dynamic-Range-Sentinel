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

# PASO 3: Invocar a juce_add_plugin en su forma más simple.
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST2 VST3 AU
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
    PLUGIN_VST2_CATEGORY  "Dynamics"
)

# PASO 4: Enlace explícito y sintácticamente puro.
# ⚡ CORRECCIÓN FINAL Y DEFINITIVA: Usamos un bucle para aplicar el enlace
# con la firma de palabra clave a cada objetivo individualmente.
# Esto elimina el conflicto de firmas.

# Primero, creamos una lista de los objetivos que realmente se van a construir.
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

# Luego, iteramos sobre la lista y enlazamos.
foreach(PLUGIN_TARGET ${PLUGIN_TARGETS})
    target_link_libraries(${PLUGIN_TARGET} PRIVATE SharedCode BinaryData)
endforeach()
