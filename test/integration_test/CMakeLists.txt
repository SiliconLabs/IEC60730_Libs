# unit test info
set(INTEGRATION_TEST_INFO "integration_test_info")
#unit test clean
set(INTEGRATION_TEST_CLEAN "integration_test_clean")

add_custom_target(${INTEGRATION_TEST_INFO}
                  COMMAND echo "Components list: integration_test_program_counter"
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
)

add_custom_target(${INTEGRATION_TEST_CLEAN}
                  COMMAND rm -rf ${CMAKE_BINARY_DIR}/test/integration_test/build/${BOARD_NAME}
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
)

include(integration_test)

generate_integration_test(test/integration_test integration_test_program_counter)