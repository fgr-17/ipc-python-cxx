# Shared Memory C++ Class Wrapper

**Author: Roux Federico (rouxfederico@gmail.com)**

# Repo information:

## Installation

This repo should be added as a submodule. The CMakeLists.txt above this file should contain the following lines:

```cmake

add_subdirectory(shmem)
target_link_libraries(${app_name} shared_mem_class)

```

