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

typedef struct {
    int num;
    char c;
} d_t;

int main(int argc, char *argv[]) {

    shmem<d_t> sh1(argv[0]);

    assert(!sh1.init());


    d_t var;

    var.num = 44;
    var.c = 'x';
    
    /* read or modify the segment, based on the command line: */
    if (argc == 2) {
        std::cout << "writing to segment: "  << var.num << " - " << var.c << std::endl;
        sh1.write(var);
    } 
    else {
        auto res = sh1.read();
        std::cout << "segment contains: "<< res.num << " - " << res.c << std::endl;
    }

    return 0;
}