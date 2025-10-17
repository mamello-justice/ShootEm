cmake_minimum_required(VERSION 3.28)

project(GameEngine)

add_library(GameEngine STATIC)

target_sources(GameEngine
    PRIVATE
    src/GameEngine.cpp
)

target_include_directories(GameEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(GameEngine PRIVATE
    sfml-system
    sfml-window
    sfml-graphics
    Core
    ImGui
)
