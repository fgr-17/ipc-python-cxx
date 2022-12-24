#include <string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

class shm {

public:

    shm(std::string path): _path(path) {}
    ~shm() {}

    int init(void);

private:

    std::string _path;
    key_t key;
    int shmid;
    char *data;
    int mode;

};