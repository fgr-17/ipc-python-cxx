cmake_minimum_required(VERSION 3.16)

project(ipc_python_cxx)

### C++
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard required for build")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "is C++ stndard a requirement")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "enable/disable compiler specific extensions")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")

set(app_name ipc_python_cxx)

add_executable (${app_name}
main.cpp)

message("App name: " ${app_name})