function(generate_iostream_usart relative_dir)

    set(FULL_DIR ${CMAKE_SOURCE_DIR}/${relative_dir})

    execute_process(COMMAND make prepare
    WORKING_DIRECTORY ${FULL_DIR})

    execute_process(COMMAND slc generate -p
        ${FULL_DIR}  -np -d ${FULL_DIR}/src -cpsdk -name=iostream_usart -o cmake --with ${BOARD_NAME}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

    if (EXISTS ${FULL_DIR}/CMakeLists.txt)
        message("-- Path have CMake File: ${FULL_DIR}/CMakeLists.txt")
        add_subdirectory(${FULL_DIR})
    else()
        message("-- Path don't have CMake File: ${FULL_DIR}")
    endif()
endfunction(generate_iostream_usart)