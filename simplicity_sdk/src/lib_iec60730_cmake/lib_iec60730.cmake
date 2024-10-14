set(SDK_PATH "/home/hieuhoang/SimplicityStudio/SDKs/gecko_sdk")
set(COPIED_SDK_PATH "gecko_sdk_4.4.2")

add_library(slc_lib_iec60730 OBJECT
    "${SDK_PATH}/hardware/board/src/sl_board_control_gpio.c"
    "${SDK_PATH}/hardware/board/src/sl_board_init.c"
    "${SDK_PATH}/hardware/driver/configuration_over_swo/src/sl_cos.c"
    "${SDK_PATH}/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c"
    "${SDK_PATH}/platform/common/src/sl_assert.c"
    "${SDK_PATH}/platform/common/src/sl_string.c"
    "${SDK_PATH}/platform/common/src/sl_syscalls.c"
    "${SDK_PATH}/platform/common/toolchain/src/sl_memory.c"
    "${SDK_PATH}/platform/Device/SiliconLabs/EFR32MG24/Source/startup_efr32mg24.c"
    "${SDK_PATH}/platform/Device/SiliconLabs/EFR32MG24/Source/system_efr32mg24.c"
    "${SDK_PATH}/platform/driver/debug/src/sl_debug_swo.c"
    "${SDK_PATH}/platform/emdrv/dmadrv/src/dmadrv.c"
    "${SDK_PATH}/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c"
    "${SDK_PATH}/platform/emdrv/uartdrv/src/uartdrv.c"
    "${SDK_PATH}/platform/emlib/src/em_burtc.c"
    "${SDK_PATH}/platform/emlib/src/em_cmu.c"
    "${SDK_PATH}/platform/emlib/src/em_core.c"
    "${SDK_PATH}/platform/emlib/src/em_emu.c"
    "${SDK_PATH}/platform/emlib/src/em_eusart.c"
    "${SDK_PATH}/platform/emlib/src/em_gpcrc.c"
    "${SDK_PATH}/platform/emlib/src/em_gpio.c"
    "${SDK_PATH}/platform/emlib/src/em_ldma.c"
    "${SDK_PATH}/platform/emlib/src/em_letimer.c"
    "${SDK_PATH}/platform/emlib/src/em_msc.c"
    "${SDK_PATH}/platform/emlib/src/em_prs.c"
    "${SDK_PATH}/platform/emlib/src/em_rmu.c"
    "${SDK_PATH}/platform/emlib/src/em_system.c"
    "${SDK_PATH}/platform/emlib/src/em_timer.c"
    "${SDK_PATH}/platform/emlib/src/em_usart.c"
    "${SDK_PATH}/platform/emlib/src/em_wdog.c"
    "${SDK_PATH}/platform/peripheral/src/peripheral_sysrtc.c"
    "${SDK_PATH}/platform/service/device_init/src/sl_device_init_dcdc_s2.c"
    "${SDK_PATH}/platform/service/device_init/src/sl_device_init_emu_s2.c"
    "${SDK_PATH}/platform/service/device_init/src/sl_device_init_hfrco.c"
    "${SDK_PATH}/platform/service/device_init/src/sl_device_init_hfxo_s2.c"
    "${SDK_PATH}/platform/service/device_init/src/sl_device_init_lfxo_s2.c"
    "${SDK_PATH}/platform/service/device_init/src/sl_device_init_nvic.c"
    "${SDK_PATH}/platform/service/iostream/src/sl_iostream.c"
    "${SDK_PATH}/platform/service/iostream/src/sl_iostream_retarget_stdio.c"
    "${SDK_PATH}/platform/service/iostream/src/sl_iostream_uart.c"
    "${SDK_PATH}/platform/service/iostream/src/sl_iostream_usart.c"
    "${SDK_PATH}/platform/service/sleeptimer/src/sl_sleeptimer.c"
    "${SDK_PATH}/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.c"
    "${SDK_PATH}/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.c"
    "${SDK_PATH}/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c"
    "${SDK_PATH}/platform/service/system/src/sl_system_init.c"
    "${SDK_PATH}/platform/service/system/src/sl_system_process_action.c"
    "${SDK_PATH}/platform/service/udelay/src/sl_udelay.c"
    "${SDK_PATH}/platform/service/udelay/src/sl_udelay_armv6m_gcc.S"
    "../autogen/sl_board_default_init.c"
    "../autogen/sl_device_init_clocks.c"
    "../autogen/sl_event_handler.c"
    "../autogen/sl_iostream_handles.c"
    "../autogen/sl_iostream_init_usart_instances.c"
)

target_include_directories(slc_lib_iec60730 PUBLIC
   "../config"
   "../autogen"
    "${SDK_PATH}/platform/Device/SiliconLabs/EFR32MG24/Include"
    "${SDK_PATH}/platform/common/inc"
    "${SDK_PATH}/hardware/board/inc"
    "${SDK_PATH}/platform/CMSIS/Core/Include"
    "${SDK_PATH}/hardware/driver/configuration_over_swo/inc"
    "${SDK_PATH}/platform/driver/debug/inc"
    "${SDK_PATH}/platform/service/device_init/inc"
    "${SDK_PATH}/platform/emdrv/dmadrv/inc"
    "${SDK_PATH}/platform/emdrv/common/inc"
    "${SDK_PATH}/platform/emlib/inc"
    "${SDK_PATH}/platform/emdrv/gpiointerrupt/inc"
    "${SDK_PATH}/platform/service/iostream/inc"
    "${SDK_PATH}/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart"
    "${SDK_PATH}/platform/peripheral/inc"
    "${SDK_PATH}/platform/common/toolchain/inc"
    "${SDK_PATH}/platform/service/system/inc"
    "${SDK_PATH}/platform/service/sleeptimer/inc"
    "${SDK_PATH}/platform/emdrv/uartdrv/inc"
    "${SDK_PATH}/platform/service/udelay/inc"
)

target_compile_definitions(slc_lib_iec60730 PUBLIC
    "SL_IEC60730_BOARD_HEADER=sl_iec60730_board.h"
    "SL_TRUSTZONE_SECURE=1"
    "EFR32MG24B220F1536IM48=1"
    "SL_BOARD_NAME=\"BRD4187C\""
    "SL_BOARD_REV=\"A01\""
    "HARDWARE_BOARD_DEFAULT_RF_BAND_2400=1"
    "HARDWARE_BOARD_SUPPORTS_1_RF_BAND=1"
    "HARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1"
    "HFXO_FREQ=39000000"
    "SL_COMPONENT_CATALOG_PRESENT=1"
)

target_link_libraries(slc_lib_iec60730 PUBLIC
    "-Wl,--start-group"
    "gcc"
    "c"
    "m"
    "nosys"
    "-Wl,--end-group"
)
target_compile_options(slc_lib_iec60730 PUBLIC
    $<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:C>:-mthumb>
    $<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Os>
    $<$<COMPILE_LANGUAGE:C>:-fdata-sections>
    $<$<COMPILE_LANGUAGE:C>:-ffunction-sections>
    $<$<COMPILE_LANGUAGE:C>:-fomit-frame-pointer>
    "$<$<COMPILE_LANGUAGE:C>:SHELL:-imacros sl_gcc_preinclude.h>"
    $<$<COMPILE_LANGUAGE:C>:-mcmse>
    $<$<COMPILE_LANGUAGE:C>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:C>:-g>
    $<$<COMPILE_LANGUAGE:CXX>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:CXX>:-mthumb>
    $<$<COMPILE_LANGUAGE:CXX>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:CXX>:-mfloat-abi=hard>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Os>
    $<$<COMPILE_LANGUAGE:CXX>:-fdata-sections>
    $<$<COMPILE_LANGUAGE:CXX>:-ffunction-sections>
    $<$<COMPILE_LANGUAGE:CXX>:-fomit-frame-pointer>
    "$<$<COMPILE_LANGUAGE:CXX>:SHELL:-imacros sl_gcc_preinclude.h>"
    $<$<COMPILE_LANGUAGE:CXX>:-mcmse>
    $<$<COMPILE_LANGUAGE:CXX>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:CXX>:-g>
    $<$<COMPILE_LANGUAGE:ASM>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:ASM>:-mthumb>
    $<$<COMPILE_LANGUAGE:ASM>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:ASM>:-mfloat-abi=hard>
    "$<$<COMPILE_LANGUAGE:ASM>:SHELL:-imacros sl_gcc_preinclude.h>"
    "$<$<COMPILE_LANGUAGE:ASM>:SHELL:-x assembler-with-cpp>"
)

set(post_build_command )
set_property(TARGET slc_lib_iec60730 PROPERTY C_STANDARD 99)
set_property(TARGET slc_lib_iec60730 PROPERTY CXX_STANDARD 11)
set_property(TARGET slc_lib_iec60730 PROPERTY CXX_EXTENSIONS OFF)

target_link_options(slc_lib_iec60730 INTERFACE
    -mcpu=cortex-m33
    -mthumb
    -mfpu=fpv5-sp-d16
    -mfloat-abi=hard
    -T${CMAKE_CURRENT_LIST_DIR}/../autogen/linkerfile_iec60730.ld
    --specs=nano.specs
    "SHELL:-Xlinker -Map=$<TARGET_FILE_DIR:lib_iec60730>/lib_iec60730.map"
    -Wl,--gc-sections
    -Wl,--no-warn-rwx-segments
)

# BEGIN_SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA
