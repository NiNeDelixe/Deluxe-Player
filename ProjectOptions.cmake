include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


include(CheckCXXSourceCompiles)


macro(Deluxe_Player_supports_sanitizers)
  # Emscripten doesn't support sanitizers
  if(EMSCRIPTEN)
    set(SUPPORTS_UBSAN OFF)
    set(SUPPORTS_ASAN OFF)
  elseif((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)

    message(STATUS "Sanity checking UndefinedBehaviorSanitizer, it should be supported on this platform")
    set(TEST_PROGRAM "int main() { return 0; }")

    # Check if UndefinedBehaviorSanitizer works at link time
    set(CMAKE_REQUIRED_FLAGS "-fsanitize=undefined")
    set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=undefined")
    check_cxx_source_compiles("${TEST_PROGRAM}" HAS_UBSAN_LINK_SUPPORT)

    if(HAS_UBSAN_LINK_SUPPORT)
      message(STATUS "UndefinedBehaviorSanitizer is supported at both compile and link time.")
      set(SUPPORTS_UBSAN ON)
    else()
      message(WARNING "UndefinedBehaviorSanitizer is NOT supported at link time.")
      set(SUPPORTS_UBSAN OFF)
    endif()
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    if (NOT WIN32)
      message(STATUS "Sanity checking AddressSanitizer, it should be supported on this platform")
      set(TEST_PROGRAM "int main() { return 0; }")

      # Check if AddressSanitizer works at link time
      set(CMAKE_REQUIRED_FLAGS "-fsanitize=address")
      set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address")
      check_cxx_source_compiles("${TEST_PROGRAM}" HAS_ASAN_LINK_SUPPORT)

      if(HAS_ASAN_LINK_SUPPORT)
        message(STATUS "AddressSanitizer is supported at both compile and link time.")
        set(SUPPORTS_ASAN ON)
      else()
        message(WARNING "AddressSanitizer is NOT supported at link time.")
        set(SUPPORTS_ASAN OFF)
      endif()
    else()
      set(SUPPORTS_ASAN ON)
    endif()
  endif()
endmacro()

macro(Deluxe_Player_setup_options)
  option(Deluxe_Player_ENABLE_HARDENING "Enable hardening" ON)
  option(Deluxe_Player_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    Deluxe_Player_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    Deluxe_Player_ENABLE_HARDENING
    OFF)

  Deluxe_Player_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR Deluxe_Player_PACKAGING_MAINTAINER_MODE)
    option(Deluxe_Player_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(Deluxe_Player_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(Deluxe_Player_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(Deluxe_Player_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(Deluxe_Player_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(Deluxe_Player_ENABLE_PCH "Enable precompiled headers" OFF)
    option(Deluxe_Player_ENABLE_CACHE "Enable ccache" OFF)
  elseif(ENABLE_DEVELOPER_MODE)
    option(Deluxe_Player_ENABLE_IPO "Enable IPO/LTO" ON)
    option(Deluxe_Player_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(Deluxe_Player_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(Deluxe_Player_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(Deluxe_Player_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(Deluxe_Player_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(Deluxe_Player_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(Deluxe_Player_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(Deluxe_Player_ENABLE_PCH "Enable precompiled headers" OFF)
    option(Deluxe_Player_ENABLE_CACHE "Enable ccache" ON)
  else()
    option(Deluxe_Player_ENABLE_IPO "Enable IPO/LTO" ON)
    option(Deluxe_Player_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(Deluxe_Player_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(Deluxe_Player_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(Deluxe_Player_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(Deluxe_Player_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(Deluxe_Player_ENABLE_PCH "Enable precompiled headers" OFF)
    option(Deluxe_Player_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      Deluxe_Player_ENABLE_IPO
      Deluxe_Player_WARNINGS_AS_ERRORS
      Deluxe_Player_ENABLE_SANITIZER_ADDRESS
      Deluxe_Player_ENABLE_SANITIZER_LEAK
      Deluxe_Player_ENABLE_SANITIZER_UNDEFINED
      Deluxe_Player_ENABLE_SANITIZER_THREAD
      Deluxe_Player_ENABLE_SANITIZER_MEMORY
      Deluxe_Player_ENABLE_UNITY_BUILD
      Deluxe_Player_ENABLE_CLANG_TIDY
      Deluxe_Player_ENABLE_CPPCHECK
      Deluxe_Player_ENABLE_LIZARD
      Deluxe_Player_ENABLE_BLOATY
      Deluxe_Player_ENABLE_COVERAGE
      Deluxe_Player_ENABLE_PCH
      Deluxe_Player_ENABLE_CACHE)
  endif()

  Deluxe_Player_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (Deluxe_Player_ENABLE_SANITIZER_ADDRESS OR Deluxe_Player_ENABLE_SANITIZER_THREAD OR Deluxe_Player_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(Deluxe_Player_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(Deluxe_Player_global_options)
  if(Deluxe_Player_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    Deluxe_Player_enable_ipo()
  endif()

  Deluxe_Player_supports_sanitizers()

  if(Deluxe_Player_ENABLE_HARDENING AND Deluxe_Player_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR Deluxe_Player_ENABLE_SANITIZER_UNDEFINED
       OR Deluxe_Player_ENABLE_SANITIZER_ADDRESS
       OR Deluxe_Player_ENABLE_SANITIZER_THREAD
       OR Deluxe_Player_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${Deluxe_Player_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${Deluxe_Player_ENABLE_SANITIZER_UNDEFINED}")
    Deluxe_Player_enable_hardening(Deluxe_Player_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(Deluxe_Player_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(Deluxe_Player_warnings INTERFACE)
  add_library(Deluxe_Player_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  Deluxe_Player_set_project_warnings(
    Deluxe_Player_warnings
    ${Deluxe_Player_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  include(cmake/Linker.cmake)
  # Must configure each target with linker options, we're avoiding setting it globally for now

  if(NOT EMSCRIPTEN)
    include(cmake/Sanitizers.cmake)
    Deluxe_Player_enable_sanitizers(
      Deluxe_Player_options
      ${Deluxe_Player_ENABLE_SANITIZER_ADDRESS}
      ${Deluxe_Player_ENABLE_SANITIZER_LEAK}
      ${Deluxe_Player_ENABLE_SANITIZER_UNDEFINED}
      ${Deluxe_Player_ENABLE_SANITIZER_THREAD}
      ${Deluxe_Player_ENABLE_SANITIZER_MEMORY})
  endif()

  set_target_properties(Deluxe_Player_options PROPERTIES UNITY_BUILD ${Deluxe_Player_ENABLE_UNITY_BUILD})

  if(Deluxe_Player_ENABLE_PCH)
    target_precompile_headers(
      Deluxe_Player_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(Deluxe_Player_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    Deluxe_Player_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(Deluxe_Player_ENABLE_CLANG_TIDY)
    Deluxe_Player_enable_clang_tidy(Deluxe_Player_options ${Deluxe_Player_WARNINGS_AS_ERRORS})
  endif()

  if(Deluxe_Player_ENABLE_CPPCHECK)
    Deluxe_Player_enable_cppcheck(${Deluxe_Player_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()
  
  if(Deluxe_Player_ENABLE_LIZARD)
    Deluxe_Player_enable_lizard(${Deluxe_Player_WARNINGS_AS_ERRORS})
  endif()
  
  if(Deluxe_Player_ENABLE_BLOATY)
    Deluxe_Player_enable_bloaty()
  endif()

  if(Deluxe_Player_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    Deluxe_Player_enable_coverage(Deluxe_Player_options)
  endif()

  if(Deluxe_Player_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(Deluxe_Player_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(Deluxe_Player_ENABLE_HARDENING AND NOT Deluxe_Player_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR Deluxe_Player_ENABLE_SANITIZER_UNDEFINED
       OR Deluxe_Player_ENABLE_SANITIZER_ADDRESS
       OR Deluxe_Player_ENABLE_SANITIZER_THREAD
       OR Deluxe_Player_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    Deluxe_Player_enable_hardening(Deluxe_Player_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
