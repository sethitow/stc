include(CTest)

file(GLOB_RECURSE test_srcs
     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     "*.cpp")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    message(STATUS ${test_srcs})

    foreach(test_src ${test_srcs}) 
        add_executable(${test_src} ${test_src})
        target_link_libraries(${test_src} gtest gmock gtest_main)

        gtest_discover_tests(${test_src})
    endforeach()
endif()
