find_package(GTest REQUIRED)
# include(GoogleTest)

# set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)

message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

file(GLOB_RECURSE PROJECT_SRCS
    "${CMAKE_SOURCE_DIR}/sources/*.cpp"
    "${CMAKE_SOURCE_DIR}/sources/math/*.cpp"
    "${CMAKE_SOURCE_DIR}/sources/physic/*.cpp" # Ensure this path is correct
)

file(GLOB_RECURSE TEST_SRCS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/math/*.cpp" # Look for .cpp files directly in the 'tests' directory
    "${CMAKE_CURRENT_SOURCE_DIR}/geometry/*.cpp" # Look for .cpp files directly in the 'tests' directory
    "${CMAKE_CURRENT_SOURCE_DIR}/physic/*.cpp" # Look for .cpp files directly in the 'tests' directory
)

add_executable(
    run_test
    ${TEST_SRCS}
    ${PROJECT_SRCS}
)

target_link_libraries(
    run_test
    GTest::gtest_main
)

target_include_directories(run_test PUBLIC
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}/includes/math
    ${CMAKE_SOURCE_DIR}/includes/physic
)

gtest_discover_tests(
    run_test
    PROPERTIES VERBOSE 1
)
