#include <iostream>
#include <zmq.hpp>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>

#include "filemanager.h"

#include <version.h>
// http://api.zeromq.org/master:zmq-inproc
// http://api.zeromq.org/2-1:zmq-ipc

const std::string imagesFolder = "../data";

int main (void) {
    std::cout << PROJECT_NAME << " " << PROJECT_VER << " started" << std::endl;
    std::cout << "Files on folder " << imagesFolder << std::endl;

    auto files = filemanager::listFilesFrom(imagesFolder, "jpg");

    auto file = filemanager::readFileBinary(imagesFolder + "/" + files[0]);
    std::cout << "file " << imagesFolder + "/" + files[0] << ", size " << file.size() << std::endl;

    // A simple test to connect to a socket
    zmq::context_t context(1);
    zmq::socket_t  socket(context, ZMQ_PUB);
    //const char * protocol = "tcp://*:5555";
    //const char * protocol = "inproc://lacface";
    const char * protocol = "ipc:///tmp/lacface";

    socket.bind(protocol);
    // for (int timeout=1; timeout <= 10; timeout++) {
    //     std::cout << timeout << std::endl;
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // }

    const std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
    const std::time_t t1_local = std::chrono::system_clock::to_time_t(t1);
    const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::cout << "Starting: " << std::put_time(std::localtime(&t1_local), "%F %T.\n") << std::endl;
    int icount = 0;
    // for (; icount < 1000000; icount++) {
    while (true) {
        zmq::message_t request((void *)file.data(), file.size(), NULL);
       //printf("(%d) Sending %lu bytes\n", icount, file.size());
        socket.send(request);
        //std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
    const std::chrono::time_point<std::chrono::system_clock> t2 = std::chrono::system_clock::now();
    const std::time_t t2_local = std::chrono::system_clock::to_time_t(t2);
    const std::chrono::time_point<std::chrono::steady_clock> stop = std::chrono::steady_clock::now();
    std::cout << "Finishing: " << std::put_time(std::localtime(&t2_local), "%F %T.\n") << std::endl;
    std::cout << "Samples: " << icount << ", Elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << " us" << std::endl;


    socket.close();
    return 0;
}