cmake_minimum_required(VERSION 3.13)



###############################################################################
## LIBRARY-PROJECT
## name and version
###############################################################################
project(VCodec VERSION 2.2.2 LANGUAGES CXX)



###############################################################################
## SETTINGS
## basic project settings before use
###############################################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")
file (GLOB_RECURSE IN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h.in)
configure_file(${IN_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Version.h)



###############################################################################
## TARGET
## create target and add include path
###############################################################################
# create glob files for *.h, *.cpp, *.hpp
file (GLOB_RECURSE H_FILES   ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file (GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# concatenate the results (glob files) to variable
set  (SOURCES ${CPP_FILES} ${H_FILES})
# create lib from src
if (NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} ${SOURCES})
endif()
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



###############################################################################
## LINK LIBRARIES
## linking all dependencies
###############################################################################
target_link_libraries(${PROJECT_NAME} Frame)



###############################################################################
## COMPILER OPTIONS
## no global instruction-set flags (see SIMD)
###############################################################################
if (MSVC)
    # EU CRA Annex I 2(k) exploit mitigation: stack cookies and control-flow guard.
    add_compile_options(/GS /guard:cf)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Oi /Ot")
else()
    add_compile_options(-O3)
    # EU CRA Annex I 2(k) exploit mitigation for the decoder that parses
    # attacker-controlled bitstreams: stack protector always, _FORTIFY_SOURCE in
    # Release. No -ffast-math and no -march=native (reproducible builds).
    add_compile_options(-fstack-protector-strong -fPIC)
    add_compile_options($<$<CONFIG:Release>:-U_FORTIFY_SOURCE>
                        $<$<CONFIG:Release>:-D_FORTIFY_SOURCE=2>)
endif()