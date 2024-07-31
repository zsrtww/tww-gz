find_program(TWWGZ_PATCHER_EXE romhack HINTS ${CMAKE_SOURCE_DIR}/bin)

if(NOT TWWGZ_PATCHER_EXE)
    message(FATAL_ERROR "please put \"romhack\" in the bin/ folder")
endif()