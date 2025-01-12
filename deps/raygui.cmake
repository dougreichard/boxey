find_package(raygui  QUIET) # QUIET or REQUIRED
if (NOT raygui_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    set(FETCHCONTENT_QUIET FALSE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

    set(FETCHCONTENT_QUIET FALSE)
    FetchContent_Declare(
        raygui
        GIT_REPOSITORY "https://github.com/raysan5/raygui.git"
        GIT_TAG "master"
        GIT_PROGRESS FALSE
    )

    FetchContent_MakeAvailable(raygui)
    #target_include_directories(raygui PUBLIC ${raygui_SOURCE_DIR})
endif()