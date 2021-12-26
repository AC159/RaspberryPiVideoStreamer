# C++ Raspberry Pi Video Streamer

## Installation on client side (must be a linux machine)

    cd client && mkdir build && cd build
    cmake ..
    make
    run the client program with: ./VideoStreamerClient
    
In order to run the client the raspberry pi server must already be running 
    and listening on a port

## Installation on Raspberry Pi 4

    cd RaspberryPiServer && mkdir build && cd build
    cmake ..
    make
    run the program and wait for incoming client connections: ./VideoStreamer
