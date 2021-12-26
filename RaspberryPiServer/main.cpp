#include <iostream>
#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "utils/socket/makeSocket.h"
#include "utils/image/sendImage.h"

using namespace std;
using namespace cv;

#define BUFFER_SIZE 1024

int main() {

    // Create a new socket on this raspberry pi and listen for incoming client requests
    int client = acceptClientRequest();

    if (client < 0) {
        cout << "Could not create socket..." << endl;
        return -1;
    }

    uint8_t buffer[BUFFER_SIZE] {0};
    uint8_t initialMessage[] = "Initializing video capture...\n";

    // Once we have a client connection, we can start the video capture
    size_t sent = send(client, initialMessage, sizeof(initialMessage), 0);
    cout << "sent: " << (int) sent << endl;

    Mat frame;

    // Initialize video capture
    VideoCapture vc{CAP_V4L2};

    // 0 = open default camera
    int deviceID = 0;

    // 0 = autodetect default API
    int apiID = CAP_ANY;

    // open selected camera using selected API
    vc.open(deviceID, apiID);

    if (!vc.isOpened()) {
        uint8_t errorMessage[] = "ERROR! Unable to open camera\n";
        wcerr << errorMessage << endl;
        send(client, errorMessage, strlen((char *) errorMessage), 0);

        // Close socket
        close(client);
        return -1;
    }

    int setCameraResolution = 2;
    int originalWidth = vc.get(CAP_PROP_FRAME_WIDTH);
    int originalHeight = vc.get(CAP_PROP_FRAME_HEIGHT);
    cout << "Width: " << originalWidth << endl;
    cout << "Height: " << originalHeight << endl;

    // --- GRAB AND WRITE LOOP
    uint8_t serverReadyMsg[] = "raspberryPi~#";
    uint8_t startVideoCapture[] = "Starting video capture...\n";
    uint8_t instruction1[] = "Press 1 to switch resolution to 176x144\n";
    uint8_t instruction2[] = "Press 2 to switch to original resolution\n";
    uint8_t instruction3[] = "Press q key to terminate\n";

    sent = send(client, startVideoCapture, sizeof(startVideoCapture), 0);
    cout << "sent: " << (int) sent << endl;
    
    sent = send(client, instruction1, sizeof(instruction1), 0);
    cout << "sent: " << (int) sent << endl;

    sent = send(client, instruction2, sizeof(instruction2), 0);
    cout << "sent: " << (int) sent << endl;

    cout << "Starting video capture..." << endl;
    cout << "Press q to quit the video streamer" << endl;

    while(true) {

        // wait for a new frame from camera and store it into 'frame'
        vc.read(frame);
        int bytesSent = sendImage(frame, client);
        cout << "Sent: " << bytesSent << endl;
        
        size_t confirmation = recv(client, buffer, 2, MSG_WAITALL); // waiting for OK from the client

        if ((int) confirmation < 0) {
            cout << "Did not receive OK status from client...ABORTING" << endl;
            break;
        }
        
        // check if we succeeded
        // if (frame.empty()) {
        //     cerr << "ERROR! blank frame grabbed\n";
        //     break;
        // }

        // if (waitKey(30) == 49 && setCameraResolution != 1) {
        //     vc.set(CAP_PROP_FRAME_WIDTH, 176);
        //     vc.set(CAP_PROP_FRAME_HEIGHT, 144);
        //     setCameraResolution = 1;
        // }

        // if (waitKey(30) == 50 && setCameraResolution != 2) {
        //     vc.set(CAP_PROP_FRAME_WIDTH, originalWidth);
        //     vc.set(CAP_PROP_FRAME_HEIGHT, originalHeight);
        //     setCameraResolution = 2;
        // }

        // show live and wait for a key with timeout long enough to show images
        // if (!frame.empty()) {
        //     imshow("Live", frame);
        // }

        if (waitKey(60) == 113)
            break;
    }

    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

