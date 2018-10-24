project(engine3)

cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)

include(CheckTypeSize)
check_type_size(long LONG_SIZE) #4 if 32bit, 8 if 64bit...

set(E3_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux)

if (LONG_SIZE EQUAL 8)
	set(E3_LIB_DIR ${E3_LIB_DIR}64)
endif ()

add_custom_target(engine3 ALL
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix
	COMMAND ${CMAKE_COMMAND} -E copy ${E3_LIB_DIR}/libengine3.a ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix/
	COMMAND ${CMAKE_COMMAND} -E copy ${E3_LIB_DIR}/libengine3-asan.a ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix/
	COMMAND ${CMAKE_COMMAND} -E copy ${E3_LIB_DIR}/libengine3-tsan.a ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix/
	COMMAND ${CMAKE_COMMAND} -E copy ${E3_LIB_DIR}/libengine3-ubsan.a ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix/
	BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix/libengine3.a ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix/libengine3-asan.a ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix/libengine3-ubsan.a ${CMAKE_CURRENT_SOURCE_DIR}/lib/unix/libengine3-tsan.a
	)
