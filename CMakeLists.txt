cmake_minimum_required(VERSION 3.15)
project(CPhysic VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}/includes/math
    ${CMAKE_SOURCE_DIR}/includes/physic
)

# file(GLOB_RECURSE APP_SRC
#     "sources/*.cpp"
#     "sources/math/*.cpp"
#     "sources/physic/*.cpp"
# )
# add_executable(cphysic ${APP_SRC})
# target_include_directories(cphysic PUBLIC
#     ${CMAKE_SOURCE_DIR}/includes
#     ${CMAKE_SOURCE_DIR}/includes/math
#     ${CMAKE_SOURCE_DIR}/includes/physic
# )

add_subdirectory(tests)

enable_testing()
