cmake_minimum_required(VERSION 3.0.0)
project(Frontend_LLVM VERSION 0.1.0)

file(GLOB_RECURSE Src src/*.h src/*.cpp)

add_executable(Frontend_LLVM main.cpp Src)

