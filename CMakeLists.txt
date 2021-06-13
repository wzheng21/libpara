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

option(BUILD_TESTS "Build tests" ON)

# Project source files
file(GLOB_RECURSE SRC_FILES "src/**/*.cc")
set(TEST_FILES "")
foreach(item ${SRC_FILES})
  if(${item} MATCHES "_test.cc$" OR ${item} MATCHES "testing_main.cc$")
    list(REMOVE_ITEM SRC_FILES ${item})
    list(APPEND TEST_FILES ${item})
  endif(${item} MATCHES "_test.cc$" OR ${item} MATCHES "testing_main.cc$")
  if(${item} MATCHES "testing_main.cc$")
    set(TEST_MAIN ${item})
  endif(${item} MATCHES "testing_main.cc$")
endforeach(item ${SRC_FILES})

message(STATUS "Source files: ${SRC_FILES}")
message(STATUS "Test files: ${TEST_FILES}")

add_library(${CMAKE_PROJECT_NAME} ${SRC_FILES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                           $<INSTALL_INTERFACE:src>)

# Necessary third parties
list(APPEND GLOG_LIB_HINTS "/usr/lib" "/usr/local/lib" "/usr/lib/x86_64-linux-gnu" ${GLOG_LIBRARIES} ${GLOG_LIBRARY})
find_library(GLOG_LIB_PATH
             NAMES glog
             HINTS GLOG_LIB_HINTS REQUIRED)
message(STATUS "Glog found at: ${GLOG_LIB_PATH}")
list(APPEND GLOG_INCLUDE_DIR_HINTS "/usr/include" "/usr/local/include" ${GLOG_INCLUDE_DIR} ${GLOG_INCLUDE_DIRS})
find_path(GLOG_INCLUDE_ROOT
          glog/logging.h
          HINTS GLOG_INCLUDE_DIR_HINTS REQUIRED)
message(STATUS "Glog include dir found at: ${GLOG_INCLUDE_ROOT}")
target_include_directories(${CMAKE_PROJECT_NAME}
                           PRIVATE ${GLOG_INCLUDE_ROOT})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${GLOG_LIB_PATH})

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

  # set up a test target per test
  foreach(test_file ${TEST_FILES})
    get_filename_component(stem ${test_file} NAME_WE)
    message("Build test: ${stem} for ${test_file}")
    add_executable(${stem} ${test_file} ${TEST_MAIN})
    target_link_libraries(${stem} PRIVATE ${CMAKE_PROJECT_NAME})
    target_link_libraries(${stem} PRIVATE GTest::GTest)
    gtest_discover_tests(${stem})
  endforeach(test_file ${TEST_FILES})
  
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
