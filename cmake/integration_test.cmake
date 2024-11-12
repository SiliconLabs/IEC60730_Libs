function(generate_integration_test relative_dir target_name)
  set(FULL_DIR ${CMAKE_SOURCE_DIR}/${relative_dir})
  set(LINKER_PATH ${CMAKE_BINARY_DIR}/${SDK_LIB_CMAKE_RELATIVE_DIR}/${LIB_IEC60730_MAP})
  set(INTEGRATION_TEST_NAME ${target_name})
  string(REPLACE "integration_test_" "" INTEGRATION_SOURCE_NAME "${INTEGRATION_TEST_NAME}")
  set(INTEGRATION_TEST_NAME_BUILD_DIR "build/${BOARD_NAME}/${target_name}")

	if(${target_name} STREQUAL "integration_test_iec60730_cpu_registers")
		set(INTEGRATION_TEST_SOURCES
    	"${FULL_DIR}/src/main.c"
    	"${FULL_DIR}/src/app.c"
    	"${FULL_DIR}/src/integration_test_common.c"
    	"${FULL_DIR}/src/${target_name}.c"
    	"${FULL_DIR}/../../lib/src/sl_iec60730_cpu_registers.c"
      "${FULL_DIR}/../../lib/src/sl_iec60730_cpu_registers_ns.c"
      "${FULL_DIR}/../../lib/src/sl_iec60730_cpu_registers_s.c"
      "${FULL_DIR}/../../lib/src/sl_iec60730_post.c"
      "${FULL_DIR}/../../lib/src/sl_iec60730_bist.c"
      "${FULL_DIR}/../../lib/src/sl_iec60730_watchdog.c"
	  )
  else()
    set(INTEGRATION_TEST_SOURCES
      "${FULL_DIR}/src/main.c"
      "${FULL_DIR}/src/app.c"
      "${FULL_DIR}/src/integration_test_common.c"
      "${FULL_DIR}/src/${target_name}.c"
      "${FULL_DIR}/../../lib/src/sl_iec60730_${INTEGRATION_SOURCE_NAME}.c"
      "${FULL_DIR}/../../lib/src/sl_iec60730_post.c"
      "${FULL_DIR}/../../lib/src/sl_iec60730_bist.c"
      "${FULL_DIR}/../../lib/src/sl_iec60730_watchdog.c"
    )
  endif()
	string(TOUPPER ${INTEGRATION_TEST_NAME} DEFINE_INTEGRATION_TEST)
	set(INTEGRATION_TEST_INCLUDES
    	"${FULL_DIR}/inc"
    	${UNITY_HEADER})
	add_executable(${INTEGRATION_TEST_NAME} ${INTEGRATION_TEST_SOURCES})
	target_include_directories(${INTEGRATION_TEST_NAME} PUBLIC ${INTEGRATION_TEST_INCLUDES})
  target_compile_definitions(${INTEGRATION_TEST_NAME} PUBLIC ${DEFINE_INTEGRATION_TEST}_ENABLE
                                                      ${DEFINE_ENABLE_CAL_CRC_32}
                                                      ${DEFINE_ENABLE_CRC_USE_SW}
                                                      ${DEFINE_ENABLE_SW_CRC_TABLE})

	target_link_libraries(${INTEGRATION_TEST_NAME} PUBLIC slc_lib_iec60730)

	# Create .bin, .hex and .s37 artifacts after building the project
	add_custom_command(TARGET ${INTEGRATION_TEST_NAME}
    	POST_BUILD
      COMMAND rm -rf ${INTEGRATION_TEST_NAME_BUILD_DIR}
    	COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:${INTEGRATION_TEST_NAME}>" "$<TARGET_FILE_DIR:${INTEGRATION_TEST_NAME}>/$<TARGET_FILE_BASE_NAME:${INTEGRATION_TEST_NAME}>.s37"
    	COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:${INTEGRATION_TEST_NAME}>" "$<TARGET_FILE_DIR:${INTEGRATION_TEST_NAME}>/$<TARGET_FILE_BASE_NAME:${INTEGRATION_TEST_NAME}>.hex"
    	COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:${INTEGRATION_TEST_NAME}>" "$<TARGET_FILE_DIR:${INTEGRATION_TEST_NAME}>/$<TARGET_FILE_BASE_NAME:${INTEGRATION_TEST_NAME}>.bin"
    	COMMAND mkdir -p ${INTEGRATION_TEST_NAME_BUILD_DIR}
    	COMMAND mv ${INTEGRATION_TEST_NAME}.out ${INTEGRATION_TEST_NAME_BUILD_DIR}
    	COMMAND mv ${INTEGRATION_TEST_NAME}.bin ${INTEGRATION_TEST_NAME_BUILD_DIR}
    	COMMAND mv ${INTEGRATION_TEST_NAME}.hex ${INTEGRATION_TEST_NAME_BUILD_DIR}
    	COMMAND mv ${INTEGRATION_TEST_NAME}.s37 ${INTEGRATION_TEST_NAME_BUILD_DIR}
      COMMAND ${CMAKE_COMMAND} -E copy ${LINKER_PATH} ${INTEGRATION_TEST_NAME_BUILD_DIR}
      COMMAND mv ${INTEGRATION_TEST_NAME_BUILD_DIR}/${LIB_IEC60730_MAP} ${INTEGRATION_TEST_NAME_BUILD_DIR}/${INTEGRATION_TEST_NAME}.map
	)

  if(${target_name} STREQUAL "integration_test_iec60730_invariable_memory")
    if(ENABLE_CAL_CRC_32)
      set(post_build_command ${CMAKE_OBJDUMP} -t -h -d -S ${INTEGRATION_TEST_NAME_BUILD_DIR}/${INTEGRATION_TEST_NAME}.out > ${INTEGRATION_TEST_NAME_BUILD_DIR}/${INTEGRATION_TEST_NAME}.lst
      && bash ${CMAKE_SOURCE_DIR}/lib/crc/sl_iec60730_cal_crc32.sh '${CMAKE_CURRENT_BINARY_DIR}/${INTEGRATION_TEST_NAME_BUILD_DIR}/${INTEGRATION_TEST_NAME}' '' 'C:/srecord/bin' '${TOOL_CHAINS}' "${FLASH_REGIONS_TEST}")
    else()
      set(post_build_command ${CMAKE_OBJDUMP} -t -h -d -S ${INTEGRATION_TEST_NAME_BUILD_DIR}/${INTEGRATION_TEST_NAME}.out > ${INTEGRATION_TEST_NAME_BUILD_DIR}/${INTEGRATION_TEST_NAME}.lst
      && bash ${CMAKE_SOURCE_DIR}/lib/crc/sl_iec60730_cal_crc16.sh '${CMAKE_CURRENT_BINARY_DIR}/${INTEGRATION_TEST_NAME_BUILD_DIR}/${INTEGRATION_TEST_NAME}' '' 'C:/srecord/bin' '${TOOL_CHAINS}' "${FLASH_REGIONS_TEST}")
    endif()
  else()
	  set(post_build_command ${CMAKE_OBJDUMP} -t -h -d -S ${INTEGRATION_TEST_NAME_BUILD_DIR}/${INTEGRATION_TEST_NAME}.out > ${INTEGRATION_TEST_NAME_BUILD_DIR}/${INTEGRATION_TEST_NAME}.lst)
  endif()
	# Run post-build pipeline to perform additional post-processing
	if(post_build_command)
	add_custom_command(TARGET ${INTEGRATION_TEST_NAME}
    	POST_BUILD
    	COMMAND ${post_build_command}
	)
	endif()
endfunction(generate_integration_test)