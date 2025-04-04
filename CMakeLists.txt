cmake_minimum_required(VERSION 3.10)
project(TinyJavaCompiler)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)

# Füge das `src/`-Verzeichnis hinzu
add_subdirectory(src)

