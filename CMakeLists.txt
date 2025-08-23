cmake_minimum_required(VERSION 3.15)

# Set vcpkg toolchain if available
if(EXISTS "/Users/akuma/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "/Users/akuma/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(XenoEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

add_library(xenoengine STATIC
    src/engine/engine.cpp
    src/xeno-pal/xeno-filesystem.cpp
    src/xeno-pal/xeno-input.cpp
    src/xeno-pal/xeno-pal-arena.cpp
    src/xeno-pal/xeno-pal-threadpool.cpp
    src/xeno-pal/xeno-window.cpp
    src/vulkan-renderer/vulkan-renderer.cpp
)

target_include_directories(xenoengine PUBLIC
    src/
    src/engine/
    src/xeno-pal/
    src/vulkan-renderer/
)


target_link_libraries(xenoengine PUBLIC Threads::Threads glfw Vulkan::Vulkan)

add_executable(xeno src/main.cpp)
target_link_libraries(xeno PRIVATE xenoengine)

enable_testing()

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)

add_executable(xeno_tests
    tests/test_main.cpp
    tests/test_engine.cpp
)

target_link_libraries(xeno_tests PRIVATE xenoengine)
target_include_directories(xeno_tests PRIVATE
    src/
    src/engine/
    tests/
)

add_test(NAME engine_tests COMMAND xeno_tests)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/examples)

add_executable(xeno_example_basic examples/example_basic.cpp)
target_link_libraries(xeno_example_basic PRIVATE xenoengine)
