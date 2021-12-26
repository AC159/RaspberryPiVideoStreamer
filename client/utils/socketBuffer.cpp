#include <opencv2/opencv.hpp>
#include <iostream>
#include "socketBuffer.h"

using namespace cv;
using namespace std;

void printBufferImageContents(uchar buffer[]) {
    cout << "Decoding image from socket: " << endl;
    Mat rawData {480*640, 1, CV_8U, buffer};
    Mat decodedImg = imdecode(rawData, IMREAD_COLOR);
    imshow("Live", decodedImg);
    waitKey(300);
}

void printBufferTextContents(const uint8_t buffer[], int BUFFER_SIZE) {
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        cout << buffer[i];
    }
}
