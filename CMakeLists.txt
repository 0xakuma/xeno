cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where to find vcpkg toolchain
# You can also pass this from the command line instead
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "/Users/akuma/dev/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()

# Set the correct vcpkg triplet for Apple Silicon Mac
if(NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET "arm64-osx")
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Find Vulkan instead of OpenGL
find_package(Vulkan REQUIRED)

add_executable(xeno 
    src/main.cpp
    src/xeno-window/xeno-window.cpp
)
target_link_libraries(xeno PRIVATE glfw imgui::imgui glm::glm Vulkan::Vulkan)