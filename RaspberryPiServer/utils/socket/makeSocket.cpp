#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

#include "makeSocket.h"

using namespace std;

int acceptClientRequest() {

    // Start a socket for listening on a port
    const int PORT = 9000;

    sockaddr_in addr;
    bzero(&addr, sizeof(addr)); // set the socket structure with null values
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; // Listen to any incoming machine
    addr.sin_port = htons(PORT);

    int s = socket(AF_INET, SOCK_STREAM, 0);

    if (s < 0) {
        cout << "Could not create socket" << endl;
        return -1;
    }

    int b = bind(s, (sockaddr *) &addr, (socklen_t) sizeof(addr));
    if (b < 0) {
        cout << "Could not bind server socket" << endl;
        return -1;
    }

    cout << "Listening for incoming client connections on port " << PORT << endl;
    int l = listen(s, 10);  // queue maximum 10 connections before refusing more connections

    if (l < 0) {
        cout << "Socket cannot listen to client requests" << endl;
        return -1;
    }

    // Accept first connection request from the queue
    size_t len = sizeof(addr);
    int client = accept(s, (sockaddr *) &addr, (socklen_t *) &len);
    if (client < 0) {
        cout << "Could not accept client connection" << endl;
        return -1;
    }
    cout << "Client connection accepted" << endl;

    return client;
}
