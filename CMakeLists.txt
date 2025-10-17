cmake_minimum_required(VERSION 3.28)

project(ShootEm LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include FetchContent for dependency management
include(FetchContent)

# Configure SFML options
set(SFML_BUILD_NETWORK TRUE)
set(SFML_BUILD_AUDIO TRUE)
set(SFML_BUILD_GRAPHICS TRUE)
set(SFML_BUILD_WINDOW TRUE)
set(SFML_BUILD_EXAMPLES FALSE)
set(SFML_BUILD_TEST_SUITE FALSE)
set(SFML_BUILD_DOC FALSE)
set(SFML_USE_STATIC_STD_LIBS FALSE)
set(SFML_GENERATE_PDB TRUE)
set(SFML_USE_SYSTEM_DEPS FALSE)

# Force MSVC to use dynamic runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Declare SFML dependency
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2)

# Make SFML available
FetchContent_MakeAvailable(SFML)

# Add subdirectories for ImGui, GameEngine & Libs
add_subdirectory(libs/core)
add_subdirectory(libs/inih)
add_subdirectory(imgui)
add_subdirectory(engine)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

# Add executable
add_executable(ShootEm)

# Add source and header files
target_sources(ShootEm
    PRIVATE
    src/main.cpp
    src/ShootEm.cpp
    PUBLIC
    include/ShootEm.h
)

# Set C++ standard for the target
target_compile_features(ShootEm PRIVATE cxx_std_23)

# Add include directories
target_include_directories(ShootEm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(ShootEm PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
    ImGui
    INIH
    Core
    GameEngine
)
