set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

cmake_minimum_required(VERSION 3.10)
project(CPhysic)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    sources
    sources/math
    includes
    includes/math
)

file(GLOB_RECURSE SRCS
    "sources/*.cpp"
    "sources/math/*.cpp"
)

# add_executable(cphysic ${SRCS} "main.cpp")

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    "tests/*.cpp"
)

add_executable(
    run_test
    ${TEST_SOURCES}
    ${SRCS}
)

target_link_libraries(
    run_test
    GTest::gtest_main
    # GTest::Main
    # pthread
)

add_test(NAME run_test COMMAND run_test)
