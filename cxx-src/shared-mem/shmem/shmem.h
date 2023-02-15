/**
 * @file shmem.h
 * @author Federico Roux (rouxfederico@gmail.com)
 * @brief C++ header for shmem.cpp
 * @version 0.1
 * @date 2022-12-24
 */

#include <string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdint.h>

#ifndef __SHMEM_H
#define __SHMEM_H

#define SHMAT_RET_ERROR ((void*) (-1))


template <class T>
class shmem {

public:

    shmem(std::string path): _path(path), data(nullptr) {}

    /**
     * @brief Destroy the shmem<T>::shmem object
     * 
     */
    ~shmem() {
        if (shmdt(static_cast<void*>(data)) == -1) {
            perror("shmdt");
        }
    }

    /**
     * @brief initialize shared memory object
     * 
     * @return int 
     */
    int init(void) {

        void* ptr;

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
        ptr = shmat(shmid, (void *)0, 0);
        if (ptr == SHMAT_RET_ERROR) {
            perror("shmat");
            return(1);
        }

        data = static_cast<T*> (ptr);
        return 0;
    }

    /**
     * @brief  write data to shared mem
     * 
     * @return char* 
     */
    int write(T data) {
        *(this->data) = data;
        return 0;
    }

    /**
     * @brief read data from shared memory
     * 
     * @return T* 
     */
    T read(void) const {
        return *data;
    }

    /**
     * @brief return size of the shared mem segment
     * 
     * @return uint16_t 
     */    
    uint16_t get_max_size(void) {
        return shm_size;
    }



private:

    std::string _path;
    key_t key;
    int shmid;
    T*data;
    int mode;

    static constexpr uint16_t shm_size = 1000;
};

#endif // __SHMEM_H