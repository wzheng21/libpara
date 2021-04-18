#This file was composed based on https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/

cmake_minimum_required(VERSION 2.8.12)

# For export versioning
if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

set(PARA_VERSION 0.0.0)

project(PARA LANGUAGES CXX VERSION ${PARA_VERSION})

option(BUILD_TESTS "Build tests" OFF)

# Project source files
file(GLOB SRC_FILES "src/para/*/*.cc")

add_library(${CMAKE_PROJECT_NAME} ${SRC_FILES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                           $<INSTALL_INTERFACE:include>)

include(GNUInstallDirs)

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
