cmake_minimum_required(VERSION 3.16)

project(ByteCodeVM
    VERSION 1.0
    DESCRIPTION "C++ Compiler Frontend + Bytecode VM"
    LANGUAGES CXX
)

# --------------------
# C++ standard
# --------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------
# Compiler warnings
# --------------------
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
    )
endif()

# --------------------
# Source files
# --------------------
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# --------------------
# Executable
# --------------------
add_executable(bytecode_vm ${SOURCES})

# --------------------
# Include directories
# --------------------
target_include_directories(bytecode_vm PRIVATE
    src
    src/Lexer
    src/Parser
    src/AST
    src/Token
    src/ByteCode
    src/VM
)

# --------------------
# Debug / Release flags
# --------------------
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(bytecode_vm PRIVATE DEBUG)
endif()
