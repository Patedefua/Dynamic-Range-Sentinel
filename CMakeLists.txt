cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C OBJCXX)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

# Configuración condicional: detectar si GUI está habilitado
set(ENABLE_GUI ON)
if(DEFINED JUCE_BUILD_GUI_CLASSES AND NOT JUCE_BUILD_GUI_CLASSES)
    set(ENABLE_GUI OFF)
endif()
if(DEFINED JUCE_USE_GUI AND NOT JUCE_USE_GUI)
    set(ENABLE_GUI OFF)
endif()

# Archivos compartidos, condicional al soporte GUI
add_library(SharedCode INTERFACE)
target_sources(SharedCode INTERFACE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
)

if(ENABLE_GUI)
    message(STATUS "✔ GUI habilitado: se incluye PluginEditor.cpp/h")
    target_sources(SharedCode INTERFACE
        Source/PluginEditor.cpp
        Source/PluginEditor.h
    )
else()
    message(STATUS "🚫 GUI deshabilitado: se excluye PluginEditor.*")
endif()

# Recursos gráficos (se compilan igual, aún sin GUI, porque pueden usarse en backends)
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

# 🔧 REDUCCIÓN ESTRATÉGICA: solo VST2
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST2
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
    PLUGIN_VST2_CATEGORY  "Dynamics"
)

# Enlace explícito del plugin a SharedCode
if(TARGET DynamicRangeSentinel_VST2)
    target_link_libraries(DynamicRangeSentinel_VST2 PRIVATE SharedCode)
endif()
