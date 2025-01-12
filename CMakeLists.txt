project(HelloWorld)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std:c++20")


add_subdirectory(deps)


add_executable(rlgui src/main_rl.cpp)
#target_include_directories(gui PUBLIC "src/cosmos")
#include_directories(igui ${SDL2_INCLUDE_DIRS})
target_link_libraries(rlgui PUBLIC  raylib rlimgui imgui)


if (MSVC)
    target_compile_options(rlgui PRIVATE /W4)
else()
    target_compile_options(rlgui PRIVATE -Wall -Wextra -pedantic)
endif()


