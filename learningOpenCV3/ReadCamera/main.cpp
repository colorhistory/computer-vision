/****************************************************************************
**
** Copyright (C) 2019 Xiaohai <xiaohaidotpro@outlook.com>.
** Contact: http://xiaohai.pro
**
** This file is part of learningOpenCV3
**
**
****************************************************************************/

#include "bits/stdc++.h"

#include "opencv2/opencv.hpp"

int main(int /* argc */, char** /* argv */) {
    cv::VideoCapture video;
    video.open(0);
    if (!video.isOpened()) {
        std::cout << "open camera failed..." << std::endl;
        return -1;
    }

    std::string windowTitle{"Window Title"};
    cv::namedWindow(windowTitle.c_str(), cv::WINDOW_GUI_NORMAL);
    cv::Mat frame;
    while (true) {
        video >> frame;
        if (frame.empty()) {
            break;
        }
        cv::imshow(windowTitle.c_str(), frame);

        if (static_cast<char>(cv::waitKey(33)) >= 0) {
            break;
        }
    }

    return 0;
}
