cmake_minimum_required(VERSION 3.24)

set(CMAKE_BUILD_TYPE Release)

if (WIN32)
    set(CMAKE_CXX_COMPILER "C:\\msys64\\mingw64\\bin\\g++.exe")
    set(CMAKE_C_COMPILER "C:\\msys64\\mingw64\\bin\\gcc.exe")
    set(CMAKE_MAKE_PROGRAM "C:/MinGW/bin/mingw32-make.exe")
endif (WIN32)

project(GearLib)

add_subdirectory(src)