cmake_minimum_required(VERSION 3.5.1)
set(NAME HuffmanSDL)
project(${NAME})
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmakeModules)
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

include_directories(${SRC_DIR}/core)

file(
  GLOB
  SRC_FILES
  ${SRC_DIR}/core/**.c
  ${SRC_DIR}/core/**.h
)

file(
  GLOB
  TEST_FILES
  ${TEST_DIR}/shared/*.c
  ${TEST_DIR}/**.cpp
 )

find_package(GTest)
find_library(SDL2_LIBRARY NAME SDL2 HINTS SDL2)

include_directories(${GTEST_INCLUDE_DIRS})

find_path(
  SDL2_INCLUDE_DIR
  NAME SDL.h
  HINTS SDL2
  PATHS /usr/include/SDL2
  )

include(CheckFlagListAndOutputString)

set(
  FLAGS
  -pedantic
  -Werror
  -Wextra
  -Wall
  -ansi
  -Wfloat-equal
)

CheckFlagListAndOutputString("${FLAGS}" CMAKE_C_FLAGS)
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})

add_library(
  ${NAME}Core
  ${SRC_FILES}
)

add_executable(
  ${NAME}
  ${SRC_DIR}/main.c
  )

include_directories(
  ${NAME}
  ${SDL2_INCLUDE_DIR}
)

target_link_libraries(
  ${NAME}
  ${NAME}Core)

target_link_libraries(
  ${NAME}Core
  ${SDL2_LIBRARY}
  -lm
)

add_executable(
  ${NAME}Test
  EXCLUDE_FROM_ALL
  ${TEST_FILES}
 )

add_custom_command(
  TARGET ${NAME}Test
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/testResources $<TARGET_FILE_DIR:${NAME}>/testResources)

add_custom_command(
  TARGET ${NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${NAME}>/resources)


include(CTest)

add_test(${NAME}Test ${NAME}Test --gtest_color=yes)

target_link_libraries(
  ${NAME}Test
  ${GTEST_MAIN_LIBRARIES}
  ${GTEST_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${NAME}Core
  )

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1
                  ${CMAKE_CTEST_COMMAND} -C $<CONFIG>
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                  COMMENT "Running tests..."
                  )

add_dependencies(check ${NAME}Test)
