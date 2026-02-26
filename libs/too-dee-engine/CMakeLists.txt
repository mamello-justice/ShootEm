cmake_minimum_required(VERSION 3.28)

project(TooDeeEngine)

# Options
set(TOO_DEE_ENGINE_BUILD_EDITOR FALSE)
set(TOO_DEE_ENGINE_BUILD_EXAMPLES FALSE)

# Fetch
include(FetchContent)

FetchContent_Declare(TooDeeEngine
    GIT_REPOSITORY https://github.com/mamello-justice/TooDeeEngine.git
    GIT_TAG 00f0ee5bd8dbdbe49a93382f5dd8811804275213 # Latest
    GIT_PROGRESS ${GIT_PROGRESS}
)

FetchContent_MakeAvailable(TooDeeEngine)
