# Get Host system distribution
execute_process(
    COMMAND uname -o
    OUTPUT_VARIABLE TWWGZ_HOST_SYS)
string(STRIP "${TWWGZ_HOST_SYS}" TWWGZ_HOST_SYS)

set(TWWGZ_ELF2REL_EXE ${CMAKE_SOURCE_DIR}/bin/elf2rel.exe)

if(TWWGZ_HOST_SYS MATCHES "Linux")
    set(TWWGZ_ELF2REL_EXE ${CMAKE_SOURCE_DIR}/bin/elf2rel)
    message(VERBOSE "We're on Linux [${TWWGZ_HOST_SYS}], found '${TWWGZ_ELF2REL_EXE}'")
else()
    message(VERBOSE "We are not on Linux [${TWWGZ_HOST_SYS}], ${TWWGZ_ELF2REL_EXE}")
endif()

if(NOT TWWGZ_ELF2REL_EXE)
    message(FATAL_ERROR "please put \"elf2rel.exe\" in the bin/ folder")
endif()