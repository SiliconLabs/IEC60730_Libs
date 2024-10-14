
function(generate_unit_test_iec60730_bist relative_dir)
  set(FULL_DIR ${CMAKE_SOURCE_DIR}/${relative_dir})
  set(UNIT_TEST_IEC60730_BIST "unit_test_iec60730_bist")
	set(UNIT_TEST_IEC60730_BIST_BUILD_DIR "build/unit_test/iec60730_bist")
	set(UNIT_TEST_SOURCES
    	"${FULL_DIR}/src/main.c"
    	"${FULL_DIR}/src/app.c"
    	"${FULL_DIR}/src/unit_test_common.c"
    	"${FULL_DIR}/src/unit_test_iec60730_bist.c"
    	"${FULL_DIR}/../../lib/src/sl_iec60730_bist.c"
	)
	set(UNIT_TEST_INCLUDES
    	"${FULL_DIR}/inc"
    	${UNITY_HEADER})

	add_executable(${UNIT_TEST_IEC60730_BIST} ${UNIT_TEST_SOURCES})
	target_include_directories(${UNIT_TEST_IEC60730_BIST} PUBLIC ${UNIT_TEST_INCLUDES})
	target_compile_definitions(${UNIT_TEST_IEC60730_BIST} PUBLIC UNIT_TEST_IEC60730_BIST_ENABLE)

	target_link_libraries(${UNIT_TEST_IEC60730_BIST} PUBLIC unity slc_lib_iec60730)

	# Create .bin, .hex and .s37 artifacts after building the project
	add_custom_command(TARGET ${UNIT_TEST_IEC60730_BIST}
    	POST_BUILD
    	COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:${UNIT_TEST_IEC60730_BIST}>" "$<TARGET_FILE_DIR:${UNIT_TEST_IEC60730_BIST}>/$<TARGET_FILE_BASE_NAME:${UNIT_TEST_IEC60730_BIST}>.s37"
    	COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:${UNIT_TEST_IEC60730_BIST}>" "$<TARGET_FILE_DIR:${UNIT_TEST_IEC60730_BIST}>/$<TARGET_FILE_BASE_NAME:${UNIT_TEST_IEC60730_BIST}>.hex"
    	COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:${UNIT_TEST_IEC60730_BIST}>" "$<TARGET_FILE_DIR:${UNIT_TEST_IEC60730_BIST}>/$<TARGET_FILE_BASE_NAME:${UNIT_TEST_IEC60730_BIST}>.bin"
    	COMMAND rm -rf ./build/bist
    	COMMAND mkdir -p ${UNIT_TEST_IEC60730_BIST_BUILD_DIR}
    	COMMAND mv ${UNIT_TEST_IEC60730_BIST}.out ${UNIT_TEST_IEC60730_BIST_BUILD_DIR}
    	COMMAND mv ${UNIT_TEST_IEC60730_BIST}.bin ${UNIT_TEST_IEC60730_BIST_BUILD_DIR}
    	COMMAND mv ${UNIT_TEST_IEC60730_BIST}.hex ${UNIT_TEST_IEC60730_BIST_BUILD_DIR}
    	COMMAND mv ${UNIT_TEST_IEC60730_BIST}.s37 ${UNIT_TEST_IEC60730_BIST_BUILD_DIR}
	)

	set(post_build_command ${CMAKE_OBJDUMP} -t -h -d -S ${UNIT_TEST_IEC60730_BIST_BUILD_DIR}/${UNIT_TEST_IEC60730_BIST}.out > ${UNIT_TEST_IEC60730_BIST_BUILD_DIR}/${UNIT_TEST_IEC60730_BIST}.lst)

	# Run post-build pipeline to perform additional post-processing
	if(post_build_command)
	add_custom_command(TARGET ${UNIT_TEST_IEC60730_BIST}
   	 	POST_BUILD
    	COMMAND ${post_build_command}
	)
	endif()
endfunction(generate_unit_test_iec60730_bist)

