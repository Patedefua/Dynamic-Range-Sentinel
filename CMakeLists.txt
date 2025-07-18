cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C OBJCXX)

# Usamos FetchContent para obtener y preparar JUCE automáticamente.
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(JUCE)

# Usamos el comando oficial de JUCE para crear el plugin.
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST2
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
    PLUGIN_VST2_CATEGORY  "Dynamics"
    SOURCE_FILES
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h
)

# Añadimos todos los recursos gráficos y tipográficos como datos binarios.
# --- LISTA COMPLETA Y VERIFICADA DE LOS 17 ARCHIVOS ---
juce_add_binary_data(BinaryData
    TARGET DynamicRangeSentinel
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
