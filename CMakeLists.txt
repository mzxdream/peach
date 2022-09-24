cmake_minimum_required(VERSION 3.20)

set(PEACH_VERSION 1.0.0)

project(peach VERSION ${PEACH_VERSION} LANGUAGES CXX)
message(STATUS "Build peach: ${PEACH_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# make sure __cplusplus is defined when using msvc and enable parallel build
if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus /MP")
endif()

set(PEACH_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${PEACH_ROOT_DIR}")

add_subdirectory(src/peach)