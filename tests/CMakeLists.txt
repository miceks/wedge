project(Google_tests)

add_subdirectory(googletest)

set(WEDGE_TESTS
    mvec_test
    ga2d_test
)

foreach(test ${WEDGE_TESTS})
    add_executable(${test} ${test}.cpp)
    target_link_libraries(${test} gtest_main wedge)
    gtest_discover_tests(${test})
    target_compile_options(${test}
        PRIVATE
            $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                -Werror
                -Wall 
                -Wextra 
                -pedantic-errors 
                -Wconversion 
                -Wsign-conversion>
            $<$<CXX_COMPILER_ID:MSVC>:
                /W4>
    )
endforeach()
