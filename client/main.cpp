#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "utils/socketBuffer.h"

using namespace std;
using namespace cv;

#define BUFFER_SIZE 1024

int main() {

    // Create a socket and connect to raspberry pi server
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.1.41");
    addr.sin_port = htons(9000);

    int s = socket(AF_INET, SOCK_STREAM, 0);

    if (s <= -1) {
        cout << "Could not create socket descriptor..." << endl;
        return -1;
    }

    int connection = connect(s, (sockaddr *) &addr, (socklen_t) sizeof(addr));

    if (connection <= -1) {
        cout << "Could not connect to the raspberry pi server..." << endl;
        return -1;
    }

    uint8_t txtBuffer[BUFFER_SIZE];
    memset(txtBuffer, 0, BUFFER_SIZE);
    uchar imgBuffer[640*480];

    size_t r = recv(s, &txtBuffer, BUFFER_SIZE, 0);
//    cout << "r: " << (int) r << endl;
    printBufferTextContents(txtBuffer, BUFFER_SIZE);
    memset(txtBuffer, 0, BUFFER_SIZE);

    r = recv(s, &txtBuffer, BUFFER_SIZE, 0);
//    cout << "r: " << (int) r << endl;
    printBufferTextContents(txtBuffer, BUFFER_SIZE);
    memset(txtBuffer, 0, BUFFER_SIZE);

    r = recv(s, &txtBuffer, BUFFER_SIZE, 0);
//    cout << "r: " << (int) r << endl;
    printBufferTextContents(txtBuffer, BUFFER_SIZE);

    size_t read, readLength, sent;
    uint imgLength = 0;
    while(true) {
        // Receive the length of the image that will come next
        readLength = recv(s, &imgLength, 4, 0);
        imgLength = imgLength;
        cout << "Incoming image length: " << imgLength << endl;
        sent = send(s, "OK", 2, 0);

        // Now, we can be sure that we receive the entire image
        read = recv(s, &imgBuffer, imgLength, MSG_WAITALL);
        cout << "Received: " << (int) read << endl;
        printBufferImageContents(imgBuffer);

        sent = send(s, "OK", 2, 0);

        if ((int) sent < 0) {
            cout << "Could not send confirmation back to server...ABORTING" << endl;
            break;
        }
    }

    return 0;
}
