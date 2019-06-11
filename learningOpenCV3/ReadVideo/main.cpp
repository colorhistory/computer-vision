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
    std::string windowTitle{"Window Title"};
    cv::namedWindow(windowTitle.c_str(), cv::WINDOW_GUI_NORMAL);

    cv::VideoCapture video(0);  // open
    if (!video.isOpened()) {
        std::cout << "load video failed..." << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        video >> frame;
        if (frame.empty()) {
            break;
        }
        cv::imshow(windowTitle.c_str(), frame);
        if (cv::waitKey(33) >= 0) {
            break;
        }
    }

    return 0;
}
