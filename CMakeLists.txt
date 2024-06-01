cmake_minimum_required(VERSION 3.16)

# Supported regions for GCN
list(APPEND TWWGZ_SUPPORTED_REGIONS NTSCU NTSCJ PAL)

if(NOT DEFINED REGION)
    # If the region is not defined, set one by default (the first in the supported list)
    list(GET TWWGZ_SUPPORTED_REGIONS 0 REGION_ELEMENT)
    set(REGION ${REGION_ELEMENT} CACHE STRING "The region of the version to be patched.")
    message(STATUS "REGION not defined, defaulting to ${REGION}")
else()
    list(FIND TWWGZ_SUPPORTED_REGIONS ${REGION} REGION_IDX)
    if(REGION_IDX EQUAL -1)
        message(FATAL_ERROR "\"${REGION}\" is not a valid region")
    endif()
endif()

if(DEFINED PR_TEST)
    set(RUN_PR_TEST "-DPR_TEST=1")
endif()

if(DEFINED DEBUG)
    set(DEBUG "-DDEBUG=1")
endif()

# Start configuring the build directory
message(STATUS "Configuring for ${REGION}...")

# These two lists are used as a map to get the right ISO file name for each version.
set(TWWGZ_ISO_VERSIONS NTSCU     NTSCJ     PAL)
set(TWWGZ_ISO_FILES    GZLE01    GZLJ01    GZLP01)

list(FIND TWWGZ_ISO_VERSIONS ${REGION} TWWGZ_ISO_VERSION)
list(GET TWWGZ_ISO_FILES ${TWWGZ_ISO_VERSION} TWWGZ_ISO_FILE)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/cmake
)

# Once we have the region ready, we can check and setup the compiler toolchain.
include(cmake/CheckDevkitPro.cmake)

include_directories(${DEVKITPRO_LIBOGC_INC})
link_directories(${DEVKITPRO_LIBOGC_LIB})

include(cmake/patcher.cmake)
include(cmake/elf2rel.cmake)
include(cmake/relmapper.cmake)
include(cmake/fonts.cmake)

project(TWWGZ
        VERSION 0.4.0
        DESCRIPTION "The Wind Waker speedrunning practice and testing tool"
        LANGUAGES C CXX ASM)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/isos)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set compiler stuff
include_directories(include external)
add_definitions(-D${REGION} -DGZ_VERSION=${CMAKE_PROJECT_VERSION} -D_PROJECT_NAME="${CMAKE_PROJECT_NAME}" -D_VERSION="${CMAKE_PROJECT_VERSION}" -D_VARIANT="public" -D_BUILDID="${CMAKE_PROJECT_VERSION}" ${DEBUG} ${RUN_PR_TEST})
add_compile_options(-fdiagnostics-color=always -fvisibility=hidden)

include(cmake/tww_c.cmake)
include(cmake/gcn_c.cmake)
include(cmake/${REGION}.cmake)

# Load the REL Loader code and parse it
file(READ "res/bin/${REGION}.bin" TWWGZ_LOADER_BIN HEX)
string(REGEX REPLACE "([0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F]?[0-9a-fA-F])" "u32 0x\\1\n" TWWGZ_CFG_LOADER_BIN ${TWWGZ_LOADER_BIN})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/patch.asm.in ${CMAKE_CURRENT_BINARY_DIR}/patch.asm)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/RomHack.toml.in ${CMAKE_CURRENT_BINARY_DIR}/RomHack.toml)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

add_subdirectory(src)
add_subdirectory(modules)

add_library(twwgz STATIC "${CPPFILES}")
add_dependencies(twwgz tww_c gcn_c modules)
set_property(TARGET twwgz PROPERTY COMPILE_FLAGS "-g -c -Os -std=gnu++20 -Wall ${DEVKITPRO_MACHDEP}")

get_target_property(TWWGZ_MODULES modules TWWGZ_MODULES)
foreach(module ${TWWGZ_MODULES})
    add_dependencies(twwgz ${module}_rel)
endforeach()

set(TWWGZ_RELS ${TWWGZ_MODULES})
list(TRANSFORM TWWGZ_RELS REPLACE "(.+)" "\\1_rel")

foreach(rel_tgt ${TWWGZ_RELS})
    get_target_property(rel_tgt_file ${rel_tgt} TWWGZ_MODULE_FILE)
    list(APPEND TWWGZ_REL_FILES ${rel_tgt_file})
endforeach()

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TWWGZ_CFG_BLD_ISO}
    DEPENDS twwgz modules ${TWWGZ_PATCHER_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_SOURCE_DIR}/isos/${TWWGZ_ISO_FILE}.iso  ${CMAKE_CURRENT_BINARY_DIR}/patch.asm ${CMAKE_CURRENT_BINARY_DIR}/RomHack.toml ${TWWGZ_REL_FILES}
    COMMAND ${TWWGZ_PATCHER_EXE} build --raw)

string(REPLACE ".iso" ".patch" TWWGZ_CFG_BLD_PATCH_OLD ${TWWGZ_CFG_BLD_ISO})
string(TOLOWER ${REGION} twwgz_region_lower)
string(REPLACE "_" "-" twwgz_region_lower ${twwgz_region_lower})
set(TWWGZ_CFG_BLD_PATCH ${CMAKE_PROJECT_VERSION}-${twwgz_region_lower}.patch)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${TWWGZ_CFG_BLD_PATCH}
    DEPENDS twwgz modules ${TWWGZ_PATCHER_EXE} ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/patch.asm ${CMAKE_CURRENT_BINARY_DIR}/RomHack.toml ${TWWGZ_REL_FILES}
    COMMAND ${TWWGZ_PATCHER_EXE} build --raw --patch
    COMMAND ${CMAKE_COMMAND} -E rename ${TWWGZ_CFG_BLD_PATCH_OLD} ${TWWGZ_CFG_BLD_PATCH})

add_custom_target(iso
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TWWGZ_CFG_BLD_ISO})

add_custom_target(patch
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${TWWGZ_CFG_BLD_PATCH})
