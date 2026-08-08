project(player VERSION 1.0.0 LANGUAGES CXX)

set(MAIN_SOURCES
  main.cpp
)

#=========================================DATA

set(LOCAL_SOURCES
  LocalTrackProvider.cpp
)

list(TRANSFORM LOCAL_SOURCES PREPEND "local/")

set(DATA_SOURCES
  ${LOCAL_SOURCES}
)

list(TRANSFORM DATA_SOURCES PREPEND "data/")

#=========================================

set(WINDOWS_SOURCES
  PlayerWindow.cpp
)

list(TRANSFORM WINDOWS_SOURCES PREPEND "windows/")

set(INTEGRATIONS_COMPONENTS_SOURCES
  IntegrationComponent.cpp
  soundcloud/SoundCloudLoginComponent.cpp
)

list(TRANSFORM INTEGRATIONS_COMPONENTS_SOURCES PREPEND "integrations/")

set(COMPONENTS_SOURCES
  MainComponent.cpp
  NavigationPanel.cpp
  PlayerBar.cpp
  TrackList.cpp
  TrackComponent.cpp
  ${INTEGRATIONS_COMPONENTS_SOURCES}
)

list(TRANSFORM COMPONENTS_SOURCES PREPEND "components/")

set(SCHEMAS_SOURCES
  LiquidGlass.cpp
)

list(TRANSFORM SCHEMAS_SOURCES PREPEND "schemas/")

set(GUI_SOURCES
  ${WINDOWS_SOURCES}
  ${COMPONENTS_SOURCES}
  ${SCHEMAS_SOURCES}
)

list(TRANSFORM GUI_SOURCES PREPEND "gui/")

#=========================================

set(TRACKS_SOURCES
  Track.cpp
)

list(TRANSFORM TRACKS_SOURCES PREPEND "tracks/")

set(MEDIA_SOURCES
  ${TRACKS_SOURCES}
)

list(TRANSFORM MEDIA_SOURCES PREPEND "media/")

#=========================================

set(SOUNDCLOUD_SOURCES
  SoundCloudIntegration.cpp
)

list(TRANSFORM SOUNDCLOUD_SOURCES PREPEND "soundcloud/")

set(INTEGRATIONS_SOURCES
  ${SOUNDCLOUD_SOURCES}
)

list(TRANSFORM INTEGRATIONS_SOURCES PREPEND "integrations//")

#=========================================

set(ALL_SOURCES
  ${MAIN_SOURCES}
  ${GUI_SOURCES}
  ${MEDIA_SOURCES}
  ${INTEGRATIONS_SOURCES}
  ${DATA_SOURCES}
)

add_executable(player ${ALL_SOURCES})

target_link_libraries(
  player
  PRIVATE Deluxe_Player::Deluxe_Player_options
          Deluxe_Player::Deluxe_Player_warnings
          juce::juce_gui_extra
          juce::juce_core
          miniaudio
          rest_request
  PUBLIC
          juce::juce_recommended_config_flags
          juce::juce_recommended_lto_flags
          juce::juce_recommended_warning_flags
)

target_include_directories(player PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include" ${CMAKE_CURRENT_SOURCE_DIR})

# qt_add_qml_module(player
#     URI hello
#     QML_FILES
#         main.qml
#         FramedImage.qml
#     RESOURCES
#         img/world.png
# )


Deluxe_Player_configure_linker(player)

target_include_directories(player PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

# Apply WASM-specific configuration
if(EMSCRIPTEN)
  Deluxe_Player_configure_wasm_target(player
    TITLE "player - FTXUI Sample"
    DESCRIPTION "FTXUI-based terminal application"
  )
endif()
