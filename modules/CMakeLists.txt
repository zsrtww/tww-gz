# Custom target that will compile all the modules at once
add_custom_target(modules)

set_property(TARGET modules PROPERTY "TWWGZ_MODULE_LAST_ID" 4096)
set(TWWGZ_MODULE_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/rels)
set(TWWGZ_MODULE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

make_directory(${TWWGZ_MODULE_OUT_DIR})

# Get source from common/rels. They are sources that have to be compiled with every REL module.
file(GLOB_RECURSE TWWGZ_EXTERNAL_REL_CPP CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/common/rels/src/*.cpp")
file(GLOB_RECURSE TWWGZ_EXTERNAL_REL_ASM CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/common/rels/src/*.s")

list(APPEND TWWGZ_EXTERNAL_REL_SRC ${TWWGZ_EXTERNAL_REL_CPP})
list(APPEND TWWGZ_EXTERNAL_REL_SRC ${TWWGZ_EXTERNAL_REL_ASM})

include_directories(${CMAKE_SOURCE_DIR}/external/)
include_directories(${CMAKE_SOURCE_DIR}/common/)

# Definition of the functions which sets up REL modules
function(twwgz_add_main_module module_name module_srcs)
    if(ARGC GREATER "2")
        set(module_inc_paths ${ARGV2})
    endif()
    if(ARGC GREATER "3")
        set(module_lib_paths ${ARGV3})
    endif()

    get_target_property(TWWGZ_MODULE_ID_COUNTER modules TWWGZ_MODULE_LAST_ID)

    add_executable(${module_name} EXCLUDE_FROM_ALL)
    target_sources(${module_name}
        PUBLIC ${module_srcs} ${TWWGZ_EXTERNAL_REL_SRC})
    target_link_libraries(${module_name} tww_c gcn_c)
    set_property(TARGET ${module_name} APPEND PROPERTY LINK_OPTIONS -Wl,-Map,${module_name}.map -Wl,--gc-sections,--gc-keep-exported -lstdc++)
    set_property(TARGET ${module_name} APPEND PROPERTY LINK_OPTIONS ${CMAKE_SOURCE_DIR}/common/rels/src/cxx.ld)

    if(module_inc_paths)
        target_include_directories(${module_name} PUBLIC ${module_inc_paths})
    endif()
    if(module_lib_paths)
        target_link_directories(${module_name} ${module_lib_paths})
    endif()

    file(GLOB relative_module_name LIST_DIRECTORIES true RELATIVE ${TWWGZ_MODULE_SRC_DIR} CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_command(OUTPUT ${TWWGZ_MODULE_OUT_DIR}/${module_name}.rel
        DEPENDS ${module_name} ${CMAKE_SOURCE_DIR}/res/map/${REGION}.lst
        COMMAND ${TWWGZ_ELF2REL_EXE} $<TARGET_FILE:${module_name}> -s ${CMAKE_SOURCE_DIR}/res/map/${REGION}.lst --rel-id ${TWWGZ_MODULE_ID_COUNTER} -o ${TWWGZ_MODULE_OUT_DIR}/${module_name}.rel)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.lst
        DEPENDS ${module_name} ${CMAKE_SOURCE_DIR}/res/map/${REGION}.lst
        COMMAND ${Python3_EXECUTABLE} ${TWWGZ_RELMAPPER_EXE} -o ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.lst -i ${CMAKE_SOURCE_DIR}/res/map/${REGION}.lst -s ${TWWGZ_MODULE_ID_COUNTER} $<TARGET_FILE:${module_name}>)
    add_custom_target(${module_name}_rel
        DEPENDS ${TWWGZ_MODULE_OUT_DIR}/${module_name}.rel ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.lst)
    set_property(TARGET ${module_name}_rel PROPERTY TWWGZ_MODULE_FILE ${TWWGZ_MODULE_OUT_DIR}/${module_name}.rel)

    set_property(TARGET modules PROPERTY TWWGZ_MAIN_MODULE_LST ${CMAKE_CURRENT_BINARY_DIR}/${module_name}.lst)
    set_property(TARGET modules PROPERTY TWWGZ_MAIN_MODULE_TRG ${module_name}_rel)
    set_property(TARGET modules PROPERTY TWWGZ_MAIN_MODULE_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    add_dependencies(modules ${module_name}_rel)
    set_property(TARGET modules APPEND PROPERTY TWWGZ_MODULES ${module_name})

    math(EXPR TWWGZ_MODULE_ID_COUNTER "${TWWGZ_MODULE_ID_COUNTER}+1")
    set_property(TARGET modules PROPERTY "TWWGZ_MODULE_LAST_ID" ${TWWGZ_MODULE_ID_COUNTER})
endfunction()

# This function will setup an individual module to be compiled and added to the dependencies of the "modules" target
function(twwgz_add_module module_name module_srcs)
    if(ARGC GREATER "2")
        set(module_inc_paths ${ARGV2})
    endif()
    if(ARGC GREATER "3")
        set(module_lib_paths ${ARGV3})
    endif()

    get_target_property(TWWGZ_MODULE_ID_COUNTER modules TWWGZ_MODULE_LAST_ID)
    get_target_property(TWWGZ_MAIN_MODULE_LST modules TWWGZ_MAIN_MODULE_LST)
    get_target_property(TWWGZ_MAIN_MODULE_TRG modules TWWGZ_MAIN_MODULE_TRG)
    get_target_property(TWWGZ_MAIN_MODULE_INC modules TWWGZ_MAIN_MODULE_INC)

    add_executable(${module_name} EXCLUDE_FROM_ALL)
    target_sources(${module_name}
        PUBLIC ${module_srcs} ${TWWGZ_EXTERNAL_REL_SRC})
    set_property(TARGET ${module_name} APPEND PROPERTY LINK_OPTIONS -Wl,-Map,${module_name}.map -Wl,--gc-sections,--gc-keep-exported)
    set_property(TARGET ${module_name} APPEND PROPERTY LINK_OPTIONS ${CMAKE_SOURCE_DIR}/common/rels/src/cxx.ld)

    target_include_directories(${module_name} PUBLIC ${TWWGZ_MAIN_MODULE_INC})

    if(module_inc_paths)
        target_include_directories(${module_name} PUBLIC ${module_inc_paths})
    endif()
    if(module_lib_paths)
        target_link_directories(${module_name} ${module_lib_paths})
    endif()

    file(GLOB relative_module_name LIST_DIRECTORIES true RELATIVE ${TWWGZ_MODULE_SRC_DIR} CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR})
    add_custom_command(OUTPUT ${TWWGZ_MODULE_OUT_DIR}/${module_name}.rel
        DEPENDS ${module_name} ${TWWGZ_MAIN_MODULE_TRG} ${TWWGZ_MAIN_MODULE_LST}
        COMMAND ${TWWGZ_ELF2REL_EXE} $<TARGET_FILE:${module_name}> -s ${TWWGZ_MAIN_MODULE_LST} --rel-id ${TWWGZ_MODULE_ID_COUNTER} -o ${TWWGZ_MODULE_OUT_DIR}/${module_name}.rel)
    add_custom_target(${module_name}_rel
        DEPENDS ${TWWGZ_MODULE_OUT_DIR}/${module_name}.rel)
    set_property(TARGET ${module_name}_rel PROPERTY TWWGZ_MODULE_FILE ${TWWGZ_MODULE_OUT_DIR}/${module_name}.rel)

    add_dependencies(modules ${module_name}_rel)
    set_property(TARGET modules APPEND PROPERTY TWWGZ_MODULES ${module_name})

    math(EXPR TWWGZ_MODULE_ID_COUNTER "${TWWGZ_MODULE_ID_COUNTER}+1")
    set_property(TARGET modules PROPERTY "TWWGZ_MODULE_LAST_ID" ${TWWGZ_MODULE_ID_COUNTER})
endfunction()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DREL_MODULE)

add_compile_options(-fdiagnostics-color=always -fno-exceptions -fno-rtti -std=gnu++20 -fno-threadsafe-statics -nostdlib -ffreestanding -ffunction-sections -fdata-sections -g -Os -Wall -Werror -Wno-address-of-packed-member -r -e_prolog -u_prolog -u_epilog -u_unresolved -Wl,--gc-sections -nostdlib -g ${DEVKITPRO_MACHDEP_LIST})
add_link_options(-r -e_prolog -u_prolog -u_epilog -u_unresolved -Wl,--gc-sections -nostdlib -g ${DEVKITPRO_MACHDEP_LIST})

file(GLOB TWWGZ_SUB_MODULES CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*")

list(REMOVE_ITEM TWWGZ_SUB_MODULES boot)
message(VERBOSE "Including main module 'boot'")
add_subdirectory(boot)

# Include all the submodules
foreach(module ${TWWGZ_SUB_MODULES})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${module})
        message(VERBOSE "Including submodule '${module}'")
        add_subdirectory(${module})
    endif()
endforeach()
