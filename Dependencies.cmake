include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(Deluxe_Player_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  # if(NOT TARGET fmtlib::fmtlib)
  #   cpmaddpackage(
  #     NAME
  #     fmt
  #     GITHUB_REPOSITORY
  #     "fmtlib/fmt"
  #     GIT_TAG
  #     "12.1.0"
  #     SYSTEM
  #     YES)
  # endif()

  # if(NOT TARGET spdlog::spdlog)
  #   cpmaddpackage(
  #     NAME
  #     spdlog
  #     VERSION
  #     1.17.0
  #     GITHUB_REPOSITORY
  #     "gabime/spdlog"
  #     SYSTEM
  #     YES
  #     OPTIONS
  #     "SPDLOG_FMT_EXTERNAL ON")
  # endif()

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage(
      NAME
      Catch2
      VERSION
      3.12.0
      GITHUB_REPOSITORY
      "catchorg/Catch2"
      SYSTEM
      YES)
  endif()

  # if(NOT TARGET CLI11::CLI11)
  #   cpmaddpackage(
  #     NAME
  #     CLI11
  #     VERSION
  #     2.6.1
  #     GITHUB_REPOSITORY
  #     "CLIUtils/CLI11"
  #     SYSTEM
  #     YES)
  # endif()

  # if(NOT TARGET ftxui::screen)
  #   cpmaddpackage(
  #     NAME
  #     FTXUI
  #     VERSION
  #     6.1.9
  #     GITHUB_REPOSITORY
  #     "ArthurSonzogni/FTXUI"
  #     SYSTEM
  #     YES)
  # endif()

  # if(NOT TARGET tools::tools)
  #   cpmaddpackage(
  #     NAME
  #     tools
  #     GITHUB_REPOSITORY
  #     "lefticus/tools"
  #     GIT_TAG
  #     "main")
  # endif()

  if(NOT TARGET ffmpeg)
    cpmaddpackage(
      NAME
      ffmpeg
      GITHUB_REPOSITORY
      "ffmpeg/ffmpeg"
      GIT_TAG
      n9.0
      SYSTEM 
      YES)
  endif()

  # find_package(Qt6 REQUIRED COMPONENTS 
  #   Core
  #   Widgets
  #   Gui
  #   #Quick
  #   Qml
  # )

  # if(NOT TARGET Qt6::Core)
  #   cpmaddpackage(
  #     NAME
  #     qtbase
  #     GITHUB_REPOSITORY
  #     "qt/qtbase"
  #     VERSION
  #     6.11.1
  #     SYSTEM
  #     YES)
  #   # list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")
  #   # set(Qt6_DIR "${CMAKE_BINARY_DIR}/lib/cmake/Qt6")
  #   # file(COPY "${CMAKE_BINARY_DIR}/_deps/qtbase-src/cmake/QtBuildInternals/QtBuildInternalsHelpers.cmake"
  #   #    DESTINATION "${CMAKE_BINARY_DIR}/lib/cmake/Qt6BuildInternals/")
  # endif()

  # if(NOT TARGET Qt6::Quick)
  #   cpmaddpackage(
  #     NAME
  #     qtdeclarative
  #     GITHUB_REPOSITORY
  #     "qt/qtdeclarative"
  #     VERSION
  #     6.11.1
  #     SYSTEM
  #     YES)
  # endif()

  if(NOT TARGET JUCE)
    cpmaddpackage(
      NAME
      JUCE
      GITHUB_REPOSITORY
      "juce-framework/JUCE"
      GIT_TAG
      9.0.0
      OPTIONS
        "JUCE_USE_WINDOWS_MIDI_SERVICES ON"
      SYSTEM 
      YES)
  endif()

  # if(NOT TARGET Qt6::Quick)
  #   set(QT_BUILD_SUBMODULES qtbase;qtdeclarative)
  #   CPMAddPackage(
  #       NAME qt5
  #       GITHUB_REPOSITORY "qt/qt5"
  #       VERSION 6.11.1
  #       OPTIONS
  #           "QT_BUILD_SUBMODULES qtbase;qtdeclarative"
  #       SYSTEM
  #       YES)
  # endif()


endfunction()
