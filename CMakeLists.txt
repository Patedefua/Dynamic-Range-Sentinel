cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C OBJCXX)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST2 VST3 AU
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
    PLUGIN_VST2_CATEGORY  "Dynamics"
    SOURCE_FILES
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h
)

# ⚡ CORRECCIÓN ESTRUCTURAL CRÍTICA: Enlace explícito del código compartido.
# Este bloque instruye al enlazador que conecte nuestro código de plugin (el "motor")
# con cada formato de salida (AU, VST3, VST2). Este es el "puente" que faltaba.
target_link_libraries(DynamicRangeSentinel_AU PRIVATE DynamicRangeSentinel_SharedCode)
target_link_libraries(DynamicRangeSentinel_VST3 PRIVATE DynamicRangeSentinel_SharedCode)

# JUCE puede decidir no construir VST2 en ciertas plataformas (como macOS arm64).
# Este condicional asegura que solo intentemos enlazarlo si el objetivo de construcción existe.
if(TARGET DynamicRangeSentinel_VST2)
    target_link_libraries(DynamicRangeSentinel_VST2 PRIVATE DynamicRangeSentinel_SharedCode)
endif()

juce_add_binary_data(BinaryData
    TARGET DynamicRangeSentinel
    SOURCES
        # ... (Lista de 17 archivos sin cambios) ...
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
