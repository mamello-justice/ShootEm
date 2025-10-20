PROGRAM := 'ShootEm'

ARCHITECTURE := 'x64'

BUILD_DIR := 'build'

CMAKE_GENERATOR := 'Visual Studio 17 2022'

default:
    just --list

setup:
    cmake -B {{BUILD_DIR}} -G "{{CMAKE_GENERATOR}}" -A {{ARCHITECTURE}}

build:
    cmake --build {{BUILD_DIR}} --config Debug

build-release:
    cmake --build {{BUILD_DIR}} --config Release

package: build-release
    dotnet build -c Release

[working-directory: 'bin']
run: build
    ../build/bin/Debug/{{PROGRAM}}
