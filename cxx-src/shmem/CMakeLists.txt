cmake_minimum_required(VERSION 3.16)

set(target_name shared_mem_class)

add_library(${target_name} shmem.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})