set(SDK_PATH "/media/sf_Work/sdk/gecko_sdk")
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
    "${SDK_PATH}/extension/devs_cooper_lighting_safty_lib/lib/inc"
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
    "SL_IEC60730_BOARD_HEADER=\"sl_iec60730_board.h\""
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
