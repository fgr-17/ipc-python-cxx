#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

int main(int argc, char *argv[])
{
   
    // /* read or modify the segment, based on the command line: */
    // if (argc == 2) {
    //     printf("writing to segment: \"%s\"\n", argv[1]);
    //     strncpy(data, argv[1], SHM_SIZE);
    // } else
    //     printf("segment contains: \"%s\"\n", data);

    // /* detach from the segment: */
    // if (shmdt(data) == -1) {
    //     perror("shmdt");
    //     exit(1);
    // }

    return 0;
}