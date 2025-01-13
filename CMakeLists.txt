project(boxey)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std:c++20")


include(deps/imgui.cmake)
include(deps/raylib.cmake)
include(deps/raygui.cmake)
include(deps/ryml.cmake)



add_executable(boxey src/main.cpp)
#
# Header only way of including: And the include folder
# ${FETCHCONTENT_BASE_DIR} points to the fetched directory
#
# Include raygui directory
target_include_directories(boxey SYSTEM PRIVATE "${FETCHCONTENT_BASE_DIR}/raygui-src/src")

target_link_libraries(boxey PUBLIC  raylib ryml::ryml)


if (MSVC)
    target_compile_options(boxey PRIVATE /W4)
else()
    target_compile_options(boxey PRIVATE -Wall -Wextra -pedantic)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
