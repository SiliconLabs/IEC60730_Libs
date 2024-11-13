function(generate_lib_iec60730 relative_dir)

    set(FULL_DIR ${CMAKE_SOURCE_DIR}/${relative_dir})

    execute_process(COMMAND make prepare
    WORKING_DIRECTORY ${FULL_DIR})

    execute_process(COMMAND slc generate -p
        ${FULL_DIR}  -np -d ${FULL_DIR}/src -cpproj -name=lib_iec60730 -o cmake --with ${BOARD_NAME}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

    if (EXISTS ${FULL_DIR}/CMakeLists.txt)
        message("-- [I] ${SDK_CMAKE_RELATIVE_DIR} path have CMake File: ${FULL_DIR}/CMakeLists.txt")
        add_subdirectory(${FULL_DIR})
    else()
        message("-- [I] ${SDK_CMAKE_RELATIVE_DIR} path don't have CMake File: ${FULL_DIR}")
    endif()
endfunction(generate_lib_iec60730)