# Define minimal required version of CMake.
cmake_minimum_required(VERSION "3.25")

# Project definition
project(
	lib_iec60730
	VERSION 1.0
	LANGUAGES C CXX ASM
)

# Include the definition of the slc_lib_iec60730 target,
# which contains the content of the SLC project
include(lib_iec60730.cmake)

add_executable(lib_iec60730
    # Add additional sources here
)

target_include_directories(lib_iec60730 PUBLIC
    # Add additional include paths here
)

target_compile_definitions(lib_iec60730 PUBLIC
    # Add additional macros here
)

target_compile_options(lib_iec60730 PUBLIC
    # Set additional compiler flags here
)

target_link_options(lib_iec60730 PUBLIC
    # Set additional linker flags here
)

# Link with the content defined in the SLC project
target_link_libraries(lib_iec60730 PRIVATE
    slc_lib_iec60730
)

# Include managed project content if available
include(lib_iec60730_project.cmake OPTIONAL RESULT_VARIABLE managed_project)
if(managed_project)
    message(STATUS "Using managed project content from ${managed_project}")
endif()

# Force the gcc linker command
set_target_properties(lib_iec60730 PROPERTIES LINKER_LANGUAGE C)

# Create .bin, .hex and .s37 artifacts after building the project
add_custom_command(TARGET lib_iec60730
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:lib_iec60730>" "$<TARGET_FILE_DIR:lib_iec60730>/$<TARGET_FILE_BASE_NAME:lib_iec60730>.s37"
    COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:lib_iec60730>" "$<TARGET_FILE_DIR:lib_iec60730>/$<TARGET_FILE_BASE_NAME:lib_iec60730>.hex"
    COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:lib_iec60730>" "$<TARGET_FILE_DIR:lib_iec60730>/$<TARGET_FILE_BASE_NAME:lib_iec60730>.bin"
)

# Run post-build pipeline to perform additional post-processing
if(post_build_command)
add_custom_command(TARGET lib_iec60730
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
    COMMAND ${post_build_command}
)
endif()
