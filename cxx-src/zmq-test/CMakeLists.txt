cmake_minimum_required(VERSION 3.16)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(zmq-test VERSION "0.1.0" LANGUAGES C CXX)

set(app_name zmq-test)

configure_file(config/version.h.in  src/version.h)

### C++
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard required for build")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "is C++ stndard a requirement")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "enable/disable compiler specific extensions")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")

message("App name: " ${app_name})

add_executable (${app_name}
src/main.cpp
src/filemanager.cpp)


# Libraries find
find_path(ZMQ_INCLUDE_DIR zmq.h)
find_library(ZMQ_LIBRARY NAMES zmq)

# Libraries link
target_link_libraries(${app_name} PRIVATE ${ZMQ_LIBRARY})
target_include_directories(${app_name} PUBLIC ${PROJECT_BINARY_DIR}/src)
