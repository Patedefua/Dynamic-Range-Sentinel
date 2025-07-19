cmake_minimum_required(VERSION 3.22)
project(DynamicRangeSentinel VERSION 1.0.1 LANGUAGES CXX C OBJCXX)

include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.10
)
FetchContent_MakeAvailable(JUCE)

# Detectar si GUI debe estar habilitado
set(ENABLE_GUI ON)
if(DEFINED JUCE_BUILD_GUI_CLASSES AND NOT JUCE_BUILD_GUI_CLASSES)
    set(ENABLE_GUI OFF)
endif()
if(DEFINED JUCE_USE_GUI AND NOT JUCE_USE_GUI)
    set(ENABLE_GUI OFF)
endif()

# Código base (sin GUI)
add_library(SharedCode INTERFACE)
target_sources(SharedCode INTERFACE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
)
target_link_libraries(SharedCode INTERFACE BinaryData)

# Agregar recursos gráficos (aunque no se use GUI)
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

# Código gráfico separado
if(ENABLE_GUI)
    add_library(GuiCode INTERFACE)
    target_sources(GuiCode INTERFACE
        Source/PluginEditor.cpp
        Source/PluginEditor.h
    )
    target_link_libraries(GuiCode INTERFACE
        juce::juce_gui_extra
        SharedCode
    )
    message(STATUS "✔ GUI habilitado: PluginEditor y juce_gui_extra incluidos")
else()
    message(STATUS "🚫 GUI deshabilitado: no se incluye PluginEditor ni juce_gui_extra")
endif()

# Definimos el plugin (solo VST2)
juce_add_plugin(DynamicRangeSentinel
    COMPANY_NAME          "OpusNexus"
    FORMATS               VST2
    BUNDLE_ID             "com.opusnexus.DynamicRangeSentinel"
    PLUGIN_VST2_CATEGORY  "Dynamics"
    IS_SYNTH              FALSE
    NEEDS_MIDI_INPUT      FALSE
    NEEDS_MIDI_OUTPUT     FALSE
    IS_MIDI_EFFECT        FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    EDITOR_IS_SUPPORTED   ${ENABLE_GUI}
)


# Vincular bibliotecas según si hay GUI
if(TARGET DynamicRangeSentinel_VST2)
    if(ENABLE_GUI)
        target_link_libraries(DynamicRangeSentinel_VST2 PRIVATE GuiCode)
    else()
        target_link_libraries(DynamicRangeSentinel_VST2 PRIVATE SharedCode)
    endif()
endif()
