#ifndef SEND_IMAGE_H
#define SEND_IMAGE_H

#include <opencv2/opencv.hpp>

int sendImage(cv::Mat frame, int socketDescriptor);

#endif