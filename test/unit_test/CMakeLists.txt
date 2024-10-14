# unit test info
set(UNIT_TEST_INFO "unit_test_info")
set(UNIT_TEST_COMPONENT
    "unit_test_iec60730_post                \
    unit_test_iec60730_bist                 \
    unit_test_iec60730_program_counter"
    )

add_custom_target(${UNIT_TEST_INFO}
                  COMMAND echo "Components list: ${UNIT_TEST_COMPONENT}"
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
)

include(unit_test)

generate_unit_test(test/unit_test unit_test_iec60730_post sl_iec60730_post.c)
generate_unit_test(test/unit_test unit_test_iec60730_bist sl_iec60730_bist.c)
generate_unit_test(test/unit_test unit_test_iec60730_program_counter sl_iec60730_program_counter.c)

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
