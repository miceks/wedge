cmake_minimum_required(VERSION 3.10.0)
project(wedge LANGUAGES CXX)

add_library(wedge INTERFACE)

target_include_directories(wedge 
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(wedge
    INTERFACE 
        cxx_std_20
)

option(WEDGE_BUILD_TESTS "Wedge tests" OFF)
if(WEDGE_BUILD_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()