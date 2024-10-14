# unit test info
set(UNIT_TEST_INFO "unit_test_info")

# Support calculate CRC
option(ENABLE_CAL_CRC_32 "Enable calculate crc 32" OFF)
option(ENABLE_CRC_USE_SW "Enable using software calculate CRC" OFF)
option(ENABLE_SW_CRC_TABLE "Enable software calculate CRC using table CRC" OFF)
set(OPTION_SUPPORT_TEST_IMC_MODULE "ENABLE_CAL_CRC_32 ENABLE_CRC_USE_SW ENABLE_SW_CRC_TABLE")

# Set address start calculate crc
if(DEFINED ENV{START_ADDR_FLASH})
  set(START_ADDR_FLASH "$ENV{START_ADDR_FLASH}")
else()
set(START_ADDR_FLASH "0x00000000")
endif()

message("-- Options to support running tests of invariable memory modules: ${OPTION_SUPPORT_TEST_IMC_MODULE}")

if(ENABLE_CAL_CRC_32)
  message("-- Support crc calculation for invariable memory modules: CRC-32")
else()
  message("-- Support crc calculation for invariable memory modules: CRC-16")
endif()

if(ENABLE_CRC_USE_SW)
  message("-- Enable using software to calculate CRC")
  if(ENABLE_SW_CRC_TABLE)
    message("-- Enable software using CRC pre-defined table to calculate CRC")
  else() # ENABLE_SW_CRC_TABLE
    message("-- Disable software using CRC pre-defined table to calculate CRC")
  endif() # ENABLE_SW_CRC_TABLE
else() # ENABLE_CRC_USE_SW
  message("-- Enable using harware GPCRC to calculate CRC")
endif() # ENABLE_CRC_USE_SW

message("-- Start address calculate crc value of flash: ${START_ADDR_FLASH}")

add_custom_target(${UNIT_TEST_INFO}
                  COMMAND echo "Components list: unit_test_iec60730_post "
                  " unit_test_iec60730_bist "
                  " unit_test_iec60730_program_counter "
                  " unit_test_iec60730_safety_check "
                  " unit_test_iec60730_irq "
                  " unit_test_iec60730_system_clock "
                  " unit_test_iec60730_watchdog "
                  " unit_test_iec60730_cpu_registers "
                  " unit_test_iec60730_variable_memory "
                  " unit_test_iec60730_invariable_memory\ "
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
generate_unit_test(test/unit_test unit_test_iec60730_variable_memory sl_iec60730_variable_memory.c)
generate_unit_test(test/unit_test unit_test_iec60730_invariable_memory sl_iec60730_invariable_memory.c)
