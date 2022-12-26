#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <shmem.h>

void shmem::~shmem() {
    /* detach from the segment: */
    if (shmdt(data) == -1) {
        perror("shmdt");
    }
}

int shmem::init(void) {

    /* make the key: */
    if ((key = ftok(_path.c_str(), 'R')) == -1) {
        perror("ftok");
        return(1);
    }

    /* connect to (and possibly create) the segment: */
    if ((shmid = shmget(key, shm_size, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        return(1);
    }

    /* attach to the segment to get a pointer to it: */
    data = (char*) shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        return(1);
    }

    return 0;
}

char* shmem::get_pointer(void) {
    return data;
}

uint16_t get_max_size(void) {
    return shm_size;
}