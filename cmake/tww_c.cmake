file(GLOB_RECURSE TWWGZ_TWW_C_CPPFILES "${CMAKE_SOURCE_DIR}/external/libtww/src/*.cpp")

add_library(tww_c STATIC "${TWWGZ_TWW_C_CPPFILES}")
set_property(TARGET tww_c PROPERTY COMPILE_FLAGS "-g -c -Os -Wall ${DEVKITPRO_MACHDEP}")
target_include_directories(tww_c PUBLIC "${CMAKE_SOURCE_DIR}/external/libtww/include")