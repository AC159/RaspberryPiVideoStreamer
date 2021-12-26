# C++ Raspberry Pi Video Streamer

## Overview

The goal is to livestream a video from a camera connected to the Raspberry Pi 
and send the live feed to the client through TCP sockets with OpenCV.

### Installation on client side (must be a linux machine)

    cd client && mkdir build && cd build
    cmake ..
    make
    run the client program with: ./VideoStreamerClient
    
In order to run the client the raspberry pi server must already be running 
    and listening on a port

### Installation on Raspberry Pi 4

    cd RaspberryPiServer && mkdir build && cd build
    cmake ..
    make
    run the program and wait for incoming client connections: ./VideoStreamer
