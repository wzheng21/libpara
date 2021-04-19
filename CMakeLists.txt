#This file was composed based on https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

# 3.10.0 is needed for gtest_discover_tests
cmake_minimum_required(VERSION 3.10.0)

# For export versioning
if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

set(PARA_VERSION 0.0.0)

project(PARA LANGUAGES CXX VERSION ${PARA_VERSION})
set(LIBNAME "${CMAKE_PROJECT_NAME}_dev")

option(BUILD_TESTS "Build tests" OFF)

# Project source files
file(GLOB_RECURSE SRC_FILES "src/**/*.cc")
set(TEST_FILES "")
foreach(item ${SRC_FILES})
  if(${item} MATCHES "_test.cc$" OR ${item} MATCHES "testing_main.cc$")
    list(REMOVE_ITEM SRC_FILES ${item})
    list(APPEND TEST_FILES ${item})
  endif(${item} MATCHES "_test.cc$" OR ${item} MATCHES "testing_main.cc$")    
endforeach(item ${SRC_FILES})

message(STATUS "Source files: ${SRC_FILES}")    
message(STATUS "Test files: ${TEST_FILES}")    

add_library(${CMAKE_PROJECT_NAME} ${SRC_FILES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                           $<INSTALL_INTERFACE:src>)

list(APPEND INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/src)
message(STATUS "Include dir: ${INTERFACE_INCLUDE_DIRECTORIES}")

message(STATUS "Current bin dir: ${CMAKE_CURRENT_BINARY_DIR}")

# Maybe build tests
message(STATUS "BUILD_TESTS: ${BUILD_TESTS}")
if(BUILD_TESTS)
  add_executable(all_tests ${TEST_FILES})
  target_link_libraries(all_tests PRIVATE ${CMAKE_PROJECT_NAME})
  enable_testing()
  find_package(GTest REQUIRED)
  message(STATUS "Found gtest: ${GTEST_BOTH_LIBRARIES}")
  #TODO: The following would not work for cmake 3.20
  target_link_libraries(all_tests PRIVATE GTest::GTest)
  gtest_discover_tests(all_tests)
endif(BUILD_TESTS)

# Install the actual library. This will export target PARA::PARA
if (NOT PARA_INSTALL_DIR)
  set(PARA_INSTALL_DIR $ENV{HOME}/opt)
endif()

install(TARGETS ${CMAKE_PROJECT_NAME}
        EXPORT para-export
        LIBRARY DESTINATION ${PARA_INSTALL_DIR}
        ARCHIVE DESTINATION ${PARA_INSTALL_DIR})

# Install the import script PARATargets.cmake
install(EXPORT para-export
        FILE ${CMAKE_PROJECT_NAME}Targets.cmake
        NAMESPACE ${CMAKE_PROJECT_NAME}::
        DESTINATION ${PARA_INSTALL_DIR}/cmake/${CMAKE_PROJECT_NAME})
