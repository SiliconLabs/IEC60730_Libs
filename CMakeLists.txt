# Define minimal required version of CMake.
cmake_minimum_required(VERSION "3.25")

# Project definition
project(
	IE60730_LIBRARY
	VERSION 1.2.0
	LANGUAGES C ASM CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_NAME iec60730)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

# enable unit test
option(ENABLE_UNIT_TESTING "Enable a Unit Testing Build" OFF)

# choose board name
option(BOARD_NAME "choose board name" brd4187c)
message("-- Board name: ${BOARD_NAME}")

#Add external libraries with Fetch Content
include(FetchContent)

if(ENABLE_UNIT_TESTING)
    FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity
        GIT_TAG v2.6.0
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(unity)
endif()

add_subdirectory(lib)
add_subdirectory(test)
# Run Make file
include(makefile)

if(ENABLE_UNIT_TESTING)

# Run generate_lib_iec60730
include(generate_lib_iec60730)

generate_lib_iec60730(gecko_sdk)
get_target_property(MAIN_CFLAGS_LIB_IEC60730 slc_lib_iec60730 COMPILE_OPTIONS)
string(REPLACE "$<$<COMPILE_LANGUAGE:C>:SHELL:-imacros sl_gcc_preinclude.h>;" "" MAIN_CFLAGS_LIB_IEC60730 "${MAIN_CFLAGS_LIB_IEC60730}")
string(REPLACE "$<$<COMPILE_LANGUAGE:CXX>:SHELL:-imacros sl_gcc_preinclude.h>;" "" MAIN_CFLAGS_LIB_IEC60730 "${MAIN_CFLAGS_LIB_IEC60730}")
string(REPLACE "$<$<COMPILE_LANGUAGE:ASM>:SHELL:-imacros sl_gcc_preinclude.h>;" "" MAIN_CFLAGS_LIB_IEC60730 "${MAIN_CFLAGS_LIB_IEC60730}")
target_compile_options(unity PUBLIC
                      ${MAIN_CFLAGS_LIB_IEC60730})

endif()


