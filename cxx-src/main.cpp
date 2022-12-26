#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <shmem.h>

int main(int argc, char *argv[]) {

    shmem sh1{"/tmp/shm1"};

    sh1.init();
    
    /* read or modify the segment, based on the command line: */
    if (argc == 2) {
        printf("writing to segment: \"%s\"\n", argv[1]);
        strncpy(sh1.get_pointer(), argv[1], sh1.get_max_size());
    } 
    else {
        printf("segment contains: \"%s\"\n", sh1.get_pointer());
    }

    return 0;
}