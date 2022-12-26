#include <string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdint.h>

#ifndef __SHMEM_H
#define __SHMEM_H


class shmem {

public:

    shmem(std::string path): _path(path) {}
    ~shmem() {}

    int init(void);
    char* get_pointer(void);

private:

    std::string _path;
    key_t key;
    int shmid;
    char *data;
    int mode;

    static constexpr uint16_t shm_size = 1000;
};

#endif // __SHMEM_H