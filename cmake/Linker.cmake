macro(Deluxe_Player_configure_linker project_name)
  set(Deluxe_Player_USER_LINKER_OPTION
    "DEFAULT"
      CACHE STRING "Linker to be used")
    set(Deluxe_Player_USER_LINKER_OPTION_VALUES "DEFAULT" "SYSTEM" "LLD" "GOLD" "BFD" "MOLD" "SOLD" "APPLE_CLASSIC" "MSVC")
  set_property(CACHE Deluxe_Player_USER_LINKER_OPTION PROPERTY STRINGS ${Deluxe_Player_USER_LINKER_OPTION_VALUES})
  list(
    FIND
    Deluxe_Player_USER_LINKER_OPTION_VALUES
    ${Deluxe_Player_USER_LINKER_OPTION}
    Deluxe_Player_USER_LINKER_OPTION_INDEX)

  if(${Deluxe_Player_USER_LINKER_OPTION_INDEX} EQUAL -1)
    message(
      STATUS
        "Using custom linker: '${Deluxe_Player_USER_LINKER_OPTION}', explicitly supported entries are ${Deluxe_Player_USER_LINKER_OPTION_VALUES}")
  endif()

  set_target_properties(${project_name} PROPERTIES LINKER_TYPE "${Deluxe_Player_USER_LINKER_OPTION}")
endmacro()
