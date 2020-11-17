cmake_minimum_required(VERSION 3.16)

enable_testing()

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

SET (CMAKE_AR "llvm-ar")
SET (CMAKE_LINKER "ld.lld")
SET (CMAKE_NM "llvm-nm")
SET (CMAKE_OBJDUMP "llvm-objdump")
SET (CMAKE_RANLIB "llvm-ranlib")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

project(Core C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(Source)
include_directories(Source/Libraries)

add_subdirectory(Source/Libraries)
add_subdirectory(Source/Main)

add_subdirectory(Tests/Libraries)
