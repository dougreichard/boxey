
find_package(ryml  QUIET) # QUIET or REQUIRED
if (NOT ryml_FOUND) # If there's none, fetch and build raylib

    set(RYML_REPO_URL https://github.com/biojppm/rapidyaml CACHE STRING "")
    set(RYML_BRANCH_NAME master CACHE STRING "")
    message(STATUS "FetchContent from repo: ${RYML_REPO_URL}")
    message(STATUS "FetchContent from branch: ${RYML_BRANCH_NAME}")
    include(FetchContent)
    FetchContent_Declare(ryml
        GIT_REPOSITORY ${RYML_REPO_URL}
        GIT_TAG ${RYML_BRANCH_NAME}
        GIT_SHALLOW FALSE  # ensure submodules are checked out
    )
    FetchContent_MakeAvailable(ryml)
    # add ryml::rymll
endif()