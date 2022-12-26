/**
 * @file main.cpp
 * @author Federico Roux (rouxfederico@gmail.com)
 * @brief example code for the shared memory class for C++
 * @version 0.1
 * @date 2022-12-24
 */

#include <iostream>
#include <cstring>
#include <cassert>

#include <shmem.h>

/**
 * @brief main
 * 
 * @param argc 2 or 3 
 * @param argv data to write on shmem [optional]
 * @return int 
 */

int main(int argc, char *argv[]) {

    shmem sh1{argv[0]};

    assert(!sh1.init());
    
    /* read or modify the segment, based on the command line: */
    if (argc == 2) {
        std::cout << "writing to segment: \"" << argv[1] << "\"" << std::endl;
        strncpy(sh1.get_pointer(), argv[1], sh1.get_max_size());
    } 
    else {
        printf("segment contains: \"%s\"\n", sh1.get_pointer());
    }

    return 0;
}