#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <opencv2/opencv.hpp>
#include "sendImage.h"

int sendImage(cv::Mat frame, int socketFD) {
    std::vector<uchar> buffer;
    // std::cout << "Frame size before sending: " << frame.size() << std::endl;
    // std::cout << "Buffer type: " << frame.type() << std::endl; 
    cv::imencode(".jpeg", frame, buffer);
    // std::cout << "Frame size after encoding: " << frame.size() << std::endl;
    // cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    // cv::imshow("Live", image);
    // cv::waitKey(0);
    std::cout << "Buffer size before sending: " << buffer.size() << std::endl;
    if (buffer.data() != NULL) {
        int imgLength = buffer.size();
        std::cout << "ImgLength converted: " << imgLength << std::endl;
        send(socketFD, &imgLength, sizeof(int), 0);

        uchar buff[2] {2};
        size_t confirmation = recv(socketFD, buff, 2, MSG_WAITALL); // waiting for OK from the client
        std::cout << "Client confirmartion: " << (int) confirmation << std::endl;
        std::cout << "Received OK from client..." << std::endl;

        if ((int) confirmation < 0) {
            std::cout << "Did not receive OK status from client...ABORTING" << std::endl;
            return -1;
        }   

        int sent = send(socketFD, buffer.data(), buffer.size(), 0);
        return sent;
    }
    return -1;
}
