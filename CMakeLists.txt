### ✅ CMakeLists.txt DEFINITIVO PARA VST2 CON GUI (WINDOWS)

cmake_minimum_required(VERSION 3.15)

project(DynamicRangeSentinel VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JUCE vía FetchContent
include(FetchContent)
FetchContent_Declare(
  juce
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG master
)
FetchContent_MakeAvailable(juce)

# Ruta al SDK VST2
set(VST2_SDK_PATH "${CMAKE_SOURCE_DIR}/vst2sdk/public.sdk/source/vst2.x")

# Agregar plugin
juce_add_plugin(DynamicRangeSentinel
  COMPANY_NAME "Patedefua"
  PLUGIN_NAME "Dynamic Range Sentinel"
  PLUGIN_MANUFACTURER_CODE PdFa
  PLUGIN_CODE DRS1
  FORMATS VST2
  PRODUCT_NAME "Dynamic Range Sentinel"
  COPY_PLUGIN_AFTER_BUILD TRUE
  PLUGIN_GUI TRUE
  SOURCE_FILES
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

# Recursos gráficos y fuentes
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

target_link_libraries(DynamicRangeSentinel
  PRIVATE
    juce::juce_audio_utils
    BinaryData
)

# Definiciones para habilitar VST2
target_compile_definitions(DynamicRangeSentinel
  PRIVATE
    JUCE_VST3_CAN_REPLACE_VST2=0
    JucePlugin_Build_VST=1
    JucePlugin_Build_VST2=1
)

# Incluir encabezados del SDK VST2
target_include_directories(DynamicRangeSentinel
  PRIVATE "${VST2_SDK_PATH}"
)


### ✅ build-windows.yml COMPLETO Y FUNCIONAL

name: Build VST2 Plugin on Windows

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build-windows:
    runs-on: windows-latest

    steps:
      - name: Checkout repository
        uses: actions/checkout@v4

      - name: Setup MSVC environment
        uses: ilammy/msvc-dev-cmd@v1

      - name: Setup CMake
        uses: jwlawson/actions-setup-cmake@v1
        with:
          cmake-version: '3.27.0'

      - name: Configure project
        run: cmake -B Builds

      - name: Build project
        run: cmake --build Builds --config Release

      - name: Find DLL and compress
        shell: pwsh
        run: |
          $dll = Get-ChildItem -Path Builds -Recurse -Filter "*.dll" | Where-Object {
            $_.FullName -match "artefacts.*Release.*\\.dll$"
          } | Select-Object -First 1

          if (-Not $dll) {
            Write-Error "❌ No DLLs were found!"
            exit 1
          }

          Write-Host "✅ Found DLL at $($dll.FullName)"
          Compress-Archive -Path $dll.FullName -DestinationPath plugin.zip

      - name: Upload artifact
        uses: actions/upload-artifact@v4
        with:
          name: DynamicRangeSentinel-VST2-Windows
          path: plugin.zip
