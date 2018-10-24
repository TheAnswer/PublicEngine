project(engine3)

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

add_custom_target(engine3 ALL
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib/unix)

set(E3_LIBS
	libengine3.a
	libengine3-asan.a
	libengine3-ubsan.a
	libengine3-tsan.a
	)

include(CheckTypeSize)
check_type_size(long LONG_SIZE) #4 if 32bit, 8 if 64bit...

set(E3_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/linux)

if (LONG_SIZE EQUAL 8)
	set(E3_LIB_DIR ${E3_LIB_DIR}64)
endif ()

foreach( file_i ${E3_LIBS})
	add_custom_command(
		TARGET engine3
		POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		ARGS -E copy ${E3_LIB_DIR}/${file_i} ${CMAKE_SOURCE_DIR}/lib/unix/
		)
endforeach( file_i )

set(ENGINE3_UBSAN_LIBRARY ${CMAKE_SOURCE_DIR}/lib/unix/libengine3-ubsan.a)
set(ENGINE3_TSAN_LIBRARY ${CMAKE_SOURCE_DIR}/lib/unix/libengine3-tsan.a)
set(ENGINE3_ASAN_LIBRARY ${CMAKE_SOURCE_DIR}/lib/unix/libengine3-asan.a)
set(ENGINE3_LIBRARY ${CMAKE_SOURCE_DIR}/lib/unix/libengine3.a)
set(ENGINE3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(IDLC_BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

IF (ENABLE_ASAN)
	SET(ENGINE3_LIBRARIES ${ENGINE3_ASAN_LIBRARY})
ELSEIF (ENABLE_TSAN)
	SET(ENGINE3_LIBRARIES ${ENGINE3_TSAN_LIBRARY})
ELSEIF (ENABLE_UBSAN)
	SET(ENGINE3_LIBRARIES ${ENGINE3_UBSAN_LIBRARY})
ELSE ()
	SET(ENGINE3_LIBRARIES ${ENGINE3_LIBRARY})
ENDIF()

SET(ENGINE3_FOUND TRUE)
SET(IDL_DIRECTIVES -outdir autogen -cp ${ENGINE3_INCLUDE_DIR})
SET(IDLC_JAVA_ARGS -XX:+TieredCompilation -XX:TieredStopAtLevel=1 -XX:+UseConcMarkSweepGC -XX:+CMSClassUnloadingEnabled -client -Xmx128M -cp ${IDLC_BIN_DIR}/idlc.jar org.sr.idlc.compiler.Compiler)
