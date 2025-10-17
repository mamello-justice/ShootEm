cmake_minimum_required(VERSION 3.28)

project(Core)

add_library(Core STATIC)

target_sources(Core
    PUBLIC
    src/Random.cpp
)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Core PRIVATE
    sfml-system)
