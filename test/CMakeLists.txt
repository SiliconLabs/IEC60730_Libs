if(ENABLE_UNIT_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(unit_test)
endif()

set(EXE_SOURCES
    "src/main.c"
    "src/Test_system.c"
    "src/Test_integrated.c"
)
set(EXE_INCLUDES "./inc")

set(EXECUTABLE_NAME Executable_Test)

add_executable(${EXECUTABLE_NAME} ${EXE_SOURCES})
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${EXE_INCLUDES})
target_link_libraries(
    ${EXECUTABLE_NAME} PUBLIC
    ${LIBRARY_IEC60730})

# Force the gcc linker command
set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINKER_LANGUAGE C)

# Create .bin, .hex and .s37 artifacts after building the project
add_custom_command(TARGET ${EXECUTABLE_NAME}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:${EXECUTABLE_NAME}>" "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/$<TARGET_FILE_BASE_NAME:${EXECUTABLE_NAME}>.s37"
    COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:${EXECUTABLE_NAME}>" "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/$<TARGET_FILE_BASE_NAME:${EXECUTABLE_NAME}>.hex"
    COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:${EXECUTABLE_NAME}>" "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/$<TARGET_FILE_BASE_NAME:${EXECUTABLE_NAME}>.bin" 
)

# Run post-build pipeline to perform additional post-processing
if(post_build_command)
add_custom_command(TARGET ${EXECUTABLE_NAME}
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
    COMMAND ${post_build_command}
)
endif()
