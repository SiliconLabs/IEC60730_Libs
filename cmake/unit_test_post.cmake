function(generate_unit_test_iec60730_post relative_dir)
  set(FULL_DIR ${CMAKE_SOURCE_DIR}/${relative_dir})
  set(UNIT_TEST_IEC60730_POST "unit_test_iec60730_post")
	set(UNIT_TEST_IEC60730_POST_BUILD_DIR "build/unit_test/iec60730_post")
	set(UNIT_TEST_SOURCES
    	"${FULL_DIR}/src/main.c"
    	"${FULL_DIR}/src/app.c"
    	"${FULL_DIR}/src/unit_test_common.c"
    	"${FULL_DIR}/src/unit_test_iec60730_post.c"
    	"${FULL_DIR}/../../lib/src/sl_iec60730_post.c"
	)
	set(UNIT_TEST_INCLUDES
    	"${FULL_DIR}/inc"
    	${UNITY_HEADER})

	add_executable(${UNIT_TEST_IEC60730_POST} ${UNIT_TEST_SOURCES})
	target_include_directories(${UNIT_TEST_IEC60730_POST} PUBLIC ${UNIT_TEST_INCLUDES})
	target_compile_definitions(${UNIT_TEST_IEC60730_POST} PUBLIC UNIT_TEST_IEC60730_POST_ENABLE)

	target_link_libraries(${UNIT_TEST_IEC60730_POST} PUBLIC unity slc_lib_iec60730)

	# Create .bin, .hex and .s37 artifacts after building the project
	add_custom_command(TARGET ${UNIT_TEST_IEC60730_POST}
    	POST_BUILD
    	COMMAND ${CMAKE_OBJCOPY} -O srec "$<TARGET_FILE:${UNIT_TEST_IEC60730_POST}>" "$<TARGET_FILE_DIR:${UNIT_TEST_IEC60730_POST}>/$<TARGET_FILE_BASE_NAME:${UNIT_TEST_IEC60730_POST}>.s37"
    	COMMAND ${CMAKE_OBJCOPY} -O ihex "$<TARGET_FILE:${UNIT_TEST_IEC60730_POST}>" "$<TARGET_FILE_DIR:${UNIT_TEST_IEC60730_POST}>/$<TARGET_FILE_BASE_NAME:${UNIT_TEST_IEC60730_POST}>.hex"
    	COMMAND ${CMAKE_OBJCOPY} -O binary "$<TARGET_FILE:${UNIT_TEST_IEC60730_POST}>" "$<TARGET_FILE_DIR:${UNIT_TEST_IEC60730_POST}>/$<TARGET_FILE_BASE_NAME:${UNIT_TEST_IEC60730_POST}>.bin"
    	COMMAND rm -rf ./build/post
    	COMMAND mkdir -p ${UNIT_TEST_IEC60730_POST_BUILD_DIR}
    	COMMAND mv ${UNIT_TEST_IEC60730_POST}.out ${UNIT_TEST_IEC60730_POST_BUILD_DIR}
    	COMMAND mv ${UNIT_TEST_IEC60730_POST}.bin ${UNIT_TEST_IEC60730_POST_BUILD_DIR}
    	COMMAND mv ${UNIT_TEST_IEC60730_POST}.hex ${UNIT_TEST_IEC60730_POST_BUILD_DIR}
    	COMMAND mv ${UNIT_TEST_IEC60730_POST}.s37 ${UNIT_TEST_IEC60730_POST_BUILD_DIR}
	)

	set(post_build_command ${CMAKE_OBJDUMP} -t -h -d -S ${UNIT_TEST_IEC60730_POST_BUILD_DIR}/${UNIT_TEST_IEC60730_POST}.out > ${UNIT_TEST_IEC60730_POST_BUILD_DIR}/${UNIT_TEST_IEC60730_POST}.lst)

	# Run post-build pipeline to perform additional post-processing
	if(post_build_command)
	add_custom_command(TARGET ${UNIT_TEST_IEC60730_POST}
    	POST_BUILD
    	COMMAND ${post_build_command}
	)
	endif()
endfunction(generate_unit_test_iec60730_post)