file(GLOB_RECURSE TWWGZ_TWW_C_CPPFILES "${CMAKE_SOURCE_DIR}/external/libtww/src/*.cpp")
file(GLOB_RECURSE TWWGZ_TWW_C_CFILES "${CMAKE_SOURCE_DIR}/external/libtww/src/*.c")

add_library(tww_c STATIC "${TWWGZ_TWW_C_CPPFILES}" "${TWWGZ_TWW_C_CFILES}")
set_property(TARGET tww_c PROPERTY COMPILE_FLAGS "-fno-builtin-sin -fno-builtin-cos -g -c -Oz -Wall ${DEVKITPRO_MACHDEP}")
target_include_directories(tww_c PUBLIC "${CMAKE_SOURCE_DIR}/external/libtww/include")