/**
 * @file shmem.cpp
 * @author Federico Roux (rouxfederico@gmail.com)
 * @brief C++ wrapper for shared memory usage on linux
 * @version 0.1
 * @date 2022-12-24
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <shmem.h>

/**
 * @brief Destroy the shmem::shmem object
 * 
 */
shmem::~shmem() {
    /* detach from the segment: */
    if (shmdt(data) == -1) {
        perror("shmdt");
    }
}

/**
 * @brief initialize shared memory object
 * 
 * @return int 
 */
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


/**
 * @brief returns shared memory's data pointer
 * 
 * @return char* 
 */
char* shmem::get_pointer(void) {
    return data;
}

/**
 * @brief return size of the shared mem segment
 * 
 * @return uint16_t 
 */
uint16_t shmem::get_max_size(void) {
    return shm_size;
}