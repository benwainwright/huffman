# Iterates through FLAG_LIST, checks whether it
# is available with the current compiler then produces
# a space separated string in OUTPUT_VAR

macro(CheckFlagListAndOutputString FLAG_LIST OUTPUT_VAR)
  unset(OUTPUT_VAR)
  include(CheckCCompilerFlag)
  foreach(FLAG ${FLAG_LIST})
    string(MAKE_C_IDENTIFIER ${FLAG} FLAG_VAR_NAME)
    check_c_compiler_flag(${FLAG} FLAG_${FLAG_VAR_NAME})
    if(FLAG_${FLAG_VAR_NAME})
      list(APPEND ${OUTPUT_VAR} ${FLAG})
    endif()
  endforeach()
  string(REPLACE ";" " " ${OUTPUT_VAR} "${${OUTPUT_VAR}}")
endmacro()
