#!/opt/venv/bin/python

import time
import zmq

if __name__ == '__main__':
    print("IPC Python C++ test: python side")



context = zmq.Context(1)
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
    #  Wait for next request from client
    message = socket.recv()
    print("Received request: %s" % message)

    #  Do some 'work'
    time.sleep(1)

    #  Send reply back to client
    socket.send(b"World")