
set(target_name shared_mem_class)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(${target_name} shmem.cpp)