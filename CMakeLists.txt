cmake_minimum_required(VERSION 3.10)

project(matrix)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED on)


# files in project:
set(SRC_DIR src)
set(SRC_C ${SRC_DIR}/matrix.c)
set(SRC_H
	${SRC_DIR}/matrix.h
	${SRC_DIR}/matrix_private.h
)

set(TESTS_DIR unit_tests)
file(GLOB TESTS_C ${TESTS_DIR}/*.c)
set(TESTS_H ${TESTS_DIR}/tests.h)

set(ALL_FILES ${SRC_C} ${SRC_H} ${TESTS_C} ${TESTS_H})


# matrix library:
set(MATRIX_LIB matrix)
add_library(${MATRIX_LIB} STATIC ${SRC_C})
target_compile_options(${MATRIX_LIB} PRIVATE
    -Wall
    -Werror
    -Wextra
)
target_include_directories(${MATRIX_LIB} PRIVATE ${SRC_DIR})
target_link_libraries(${MATRIX_LIB} PRIVATE m)


# check.h dependencies:
find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_CHECK REQUIRED check)


# tests build:
set(TEST_TARGET tests.out)
add_executable(${TEST_TARGET} ${TESTS_C})
target_include_directories(${TEST_TARGET} PRIVATE
    ${SRC_DIR}
    ${TESTS_DIR}
)
target_link_libraries(${TEST_TARGET}
    ${MATRIX_LIB}
    ${PC_CHECK_LIBRARIES}
)


# tests run:
add_custom_target(test
	DEPENDS ${TEST_TARGET}
	COMMAND ./${TEST_TARGET}
	COMMENT "Testing... "
)


# valgrind run:
add_custom_target(mem
	DEPENDS ${TEST_TARGET}
	COMMAND valgrind
		--child-silent-after-fork=yes
		--track-origins=yes
		--leak-check=full
		--show-leak-kinds=all
		--show-error-list=yes
		./${TEST_TARGET}
	COMMENT "Memory checking..."
)


# clang-format:
set(CLANG_FORMAT_CONFIG ${CMAKE_SOURCE_DIR}/linter/.clang-format)
find_program(CLANG_FORMAT clang-format)
add_custom_target(clang-format
	COMMAND ${CLANG_FORMAT} -i --style=file:${CLANG_FORMAT_CONFIG} ${ALL_FILES}
	COMMENT "Formatting code..."
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)