get_filename_component(dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TWWGZ_MODULE_OUT_DIR ${TWWGZ_MODULE_OUT_DIR}/${dir_name})
make_directory(${TWWGZ_MODULE_OUT_DIR})

file(GLOB TWWGZ_FEATURES_MODULES CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*")

# Include all the submodules
foreach(module ${TWWGZ_FEATURES_MODULES})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${module})
        message(VERBOSE "Including feature module '${module}'")
        add_subdirectory(${module})
    endif()
endforeach()