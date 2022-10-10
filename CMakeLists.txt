# 2021-∞ (c) blurryroots innovation qanat OÜ. All rights reserved.
# See license.md for details.

# Version 3.2 and upwards.
CMAKE_MINIMUM_REQUIRED (VERSION 3.2)

# Setup versioning.
set (BUILD_MAJOR 0)
set (BUILD_MINOR 3)
set (BUILD_PATCH 3)
set (BUILD_VERSION "${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_PATCH}")

# Expose version information to config.
set (VERSION_NAME_BUFFER_SIZE 16)
set (VERSION_MAJOR ${BUILD_MAJOR})
set (VERISON_MINOR ${BUILD_MINOR})
set (VERSION_PATCH ${BUILD_PATCH})
set (VERSION_FORMAT "v%d.%d.%d")

# Specify version for this project.
project (spirits VERSION ${BUILD_VERSION})

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Release" CACHE PATH "" FORCE)
endif ()

if (USE_GEDANKEN)
    ADD_DEFINITIONS (-DUSE_GEDANKEN=1)
endif ()

string (
    COMPARE EQUAL
    "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    IS_STANDALON_PROJECT
)

# .
option (BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Make sure libraries will be places beside executable.
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        ADD_DEFINITIONS(-DUCRTBASEDLL_NAME="ucrtbase.dll")
    else ()
        ADD_DEFINITIONS(-DUCRTBASEDLL_NAME="ucrtbased.dll")
    endif ()
endif()

if (MSVC)
    # warning level 4 and all warnings as errors
    #add_compile_options(/W4 /WX)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options (-Wunused-result)
endif ()

# Collect source and header files.
file (GLOB_RECURSE SRC
    ${PROJECT_SOURCE_DIR}/src/*.c
)
add_library (spirits ${SRC})
target_include_directories (spirits PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc/>
)
set_property (TARGET spirits PROPERTY C_STANDARD 11)

#.
add_executable (spirits-example-allocation EXCLUDE_FROM_ALL
    ${PROJECT_SOURCE_DIR}/examples/allocation.c
)
set_property (TARGET spirits-example-allocation PROPERTY C_STANDARD 17)
add_dependencies (spirits-example-allocation spirits)
target_link_libraries (spirits-example-allocation spirits)