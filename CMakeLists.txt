cmake_minimum_required(VERSION 3.13)



################################################################################
## PROJECT
## name and version
################################################################################
project(VCodec LANGUAGES CXX)



################################################################################
## SETTINGS
## basic project settings before use
################################################################################
# If this project is used as a submodule, the variable should be overridden
# to "OFF" in the top-level application (to disable forced cache rewriting)
option(${PARENT}_SUBMODULE_CACHE_OVERWRITE "Enable forced cache rewriting" ON)
if (${PARENT}_SUBMODULE_CACHE_OVERWRITE)
    SET(REWRITE_FORCE "FORCE")
else()
    SET(REWRITE_FORCE "")
endif()

# Set default Release mode if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type defaulting to Release" FORCE)
endif()



################################################################################
## CONFIGURATION
## project configuration
################################################################################
SET(${PARENT}_VCODEC                         ON  CACHE BOOL "" ${REWRITE_FORCE})



################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the project configuration
################################################################################
if (${PARENT}_VCODEC)
    # If this project is a stand alone repository, its dependency is expected
    # to be next to it (../Frame) and is added first. If this project is
    # included in another one, the top-level CMakeLists.txt must add this
    # library by itself.
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Frame ${CMAKE_CURRENT_BINARY_DIR}/Frame)
    endif()
    add_subdirectory(src)
endif()
