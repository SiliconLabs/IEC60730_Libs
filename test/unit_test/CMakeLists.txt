# unit test info
set(UNIT_TEST_INFO "unit_test_info")

add_custom_target(${UNIT_TEST_INFO}
                  COMMAND echo "Components list: unit_test_iec60730_post "
                  " unit_test_iec60730_bist "
                  " unit_test_iec60730_program_counter "
                  " unit_test_iec60730_safety_check "
                  " unit_test_iec60730_irq "
                  " unit_test_iec60730_system_clock "
                  " unit_test_iec60730_watchdog "
                  " unit_test_iec60730_cpu_registers\ "
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
)

include(unit_test)

generate_unit_test(test/unit_test unit_test_iec60730_post sl_iec60730_post.c)
generate_unit_test(test/unit_test unit_test_iec60730_bist sl_iec60730_bist.c)
generate_unit_test(test/unit_test unit_test_iec60730_program_counter sl_iec60730_program_counter.c)
generate_unit_test(test/unit_test unit_test_iec60730_safety_check sl_iec60730_bist.c)
generate_unit_test(test/unit_test unit_test_iec60730_irq sl_iec60730_irq.c)
generate_unit_test(test/unit_test unit_test_iec60730_system_clock sl_iec60730_system_clock.c)
generate_unit_test(test/unit_test unit_test_iec60730_watchdog sl_iec60730_watchdog.c)
generate_unit_test(test/unit_test unit_test_iec60730_cpu_registers sl_iec60730_cpu_registers)

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