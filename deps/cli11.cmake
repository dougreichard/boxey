
find_package(cli11  QUIET) # QUIET or REQUIRED
if (NOT cli11_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
        cli11_proj
        QUIET
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG v2.4.2
    )

    FetchContent_MakeAvailable(cli11_proj)
endif()