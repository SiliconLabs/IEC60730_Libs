set(UNIT_TEST_INFO "unit_test_info")
set(UNIT_TEST_COMPONENT "module_demo")

add_custom_target(${UNIT_TEST_INFO}
                  COMMAND echo "Components list: ${UNIT_TEST_COMPONENT}" || (exit 0)
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
)


set(UNIT_TEST_MODULE_DEMO "unit_test_iec60730_module_demo")
set(UNIT_TEST_MODULE_DEMO_BUILD_DIR "build/moule_demo")
set(UNIT_TEST_SOURCES
    "./src/main.c"
    "./src/app.c"
    "./src/test_common.c"
    "./src/test_iec60730_module_demo.c"
)
set(UNIT_TEST_INCLUDES "./inc"
   ${UNITY_HEADER})

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Build)
add_executable(${UNIT_TEST_MODULE_DEMO} ${UNIT_TEST_SOURCES})
target_include_directories(${UNIT_TEST_MODULE_DEMO} PUBLIC ${UNIT_TEST_INCLUDES})

target_link_libraries(${UNIT_TEST_MODULE_DEMO} PUBLIC unity slc_iostream_usart )

# Create .bin, .hex and .s37 artifacts after building the project
add_custom_command(TARGET ${UNIT_TEST_MODULE_DEMO}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:${UNIT_TEST_MODULE_DEMO}>" "$<TARGET_FILE_DIR:${UNIT_TEST_MODULE_DEMO}>/$<TARGET_FILE_BASE_NAME:${UNIT_TEST_MODULE_DEMO}>.s37"
    COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:${UNIT_TEST_MODULE_DEMO}>" "$<TARGET_FILE_DIR:${UNIT_TEST_MODULE_DEMO}>/$<TARGET_FILE_BASE_NAME:${UNIT_TEST_MODULE_DEMO}>.hex"
    COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:${UNIT_TEST_MODULE_DEMO}>" "$<TARGET_FILE_DIR:${UNIT_TEST_MODULE_DEMO}>/$<TARGET_FILE_BASE_NAME:${UNIT_TEST_MODULE_DEMO}>.bin"
    COMMAND rm -rf ./build
    COMMAND mkdir -p ${UNIT_TEST_MODULE_DEMO_BUILD_DIR}
    COMMAND mv ${UNIT_TEST_MODULE_DEMO}.out ${UNIT_TEST_MODULE_DEMO_BUILD_DIR}
    COMMAND mv ${UNIT_TEST_MODULE_DEMO}.bin ${UNIT_TEST_MODULE_DEMO_BUILD_DIR}
    COMMAND mv ${UNIT_TEST_MODULE_DEMO}.hex ${UNIT_TEST_MODULE_DEMO_BUILD_DIR}
    COMMAND mv ${UNIT_TEST_MODULE_DEMO}.s37 ${UNIT_TEST_MODULE_DEMO_BUILD_DIR}
)

set(post_build_command ${CMAKE_OBJDUMP} -t -h -d -S ${UNIT_TEST_MODULE_DEMO_BUILD_DIR}/${UNIT_TEST_MODULE_DEMO}.out > ${UNIT_TEST_MODULE_DEMO_BUILD_DIR}/${UNIT_TEST_MODULE_DEMO}.lst)

# Run post-build pipeline to perform additional post-processing
if(post_build_command)
add_custom_command(TARGET ${UNIT_TEST_MODULE_DEMO}
    POST_BUILD
    COMMAND ${post_build_command}
)
endif()

if(${CORE_TYPE} MATCHES "cortex-m33")
target_compile_options(unity PUBLIC
    $<$<COMPILE_LANGUAGE:C>:-mcpu=${CORE_TYPE}>
    $<$<COMPILE_LANGUAGE:C>:-mthumb>
    $<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Os>)
elseif(${CORE_TYPE} MATCHES "cortex-m4")
target_compile_options(unity PUBLIC
    $<$<COMPILE_LANGUAGE:C>:-mcpu=${CORE_TYPE}>
    $<$<COMPILE_LANGUAGE:C>:-mthumb>
    $<$<COMPILE_LANGUAGE:C>:-mfpu=fpv4-sp-d16>
    $<$<COMPILE_LANGUAGE:C>:-mfloat-abi=softfp>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Os>)
endif()
