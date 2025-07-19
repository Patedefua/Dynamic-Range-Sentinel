cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C OBJCXX)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

# ⚡ PARADIGMA 1: AISLAR NUESTRO CÓDIGO
# Creamos una biblioteca "INTERFACE" (sin compilación propia) solo para agrupar nuestros archivos fuente.
add_library(SharedCode INTERFACE)
target_sources(SharedCode INTERFACE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

# ⚡ PARADIGMA 2: AISLAR NUESTROS RECURSOS
# El comando juce_add_binary_data ya crea un objetivo llamado "BinaryData".
juce_add_binary_data(BinaryData
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

# ⚡ PARADIGMA 3: ENSAMBLAJE EXPLÍCITO
# Le decimos a juce_add_plugin que construya el plugin, pero en lugar de darle los archivos
# fuente directamente, le decimos que enlace y consuma nuestras bibliotecas predefinidas.
# Esto elimina toda ambigüedad y previene el enlace duplicado.
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST2 VST3 AU
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
    PLUGIN_VST2_CATEGORY  "Dynamics"
    # El enlace se define aquí, de forma clara y única.
    LINK_LIBRARIES
        SharedCode
        BinaryData
)

# Ya no son necesarios los enlaces manuales `target_link_libraries`.
# La directiva LINK_LIBRARIES anterior los hace obsoletos y dañinos.
