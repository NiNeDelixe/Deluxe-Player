project(player VERSION 1.0.0 LANGUAGES CXX)

set(MAIN_SOURCES
  main.cpp
)

set(WINDOWS_SOURCES
  PlayerWindow.cpp
  PlayerWindow.hpp
)

list(TRANSFORM WINDOWS_SOURCES PREPEND "windows/")

set(GUI_SOURCES
  ${WINDOWS_SOURCES}
)

list(TRANSFORM GUI_SOURCES PREPEND "gui/")

set(ALL_SOURCES
  ${MAIN_SOURCES}
  ${GUI_SOURCES}
)

add_executable(player ${ALL_SOURCES})

target_link_libraries(
  player
  PRIVATE Deluxe_Player::Deluxe_Player_options
          Deluxe_Player::Deluxe_Player_warnings
          juce::juce_gui_extra
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
