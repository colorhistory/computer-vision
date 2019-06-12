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
    cv::VideoCapture cap("../../materials/video.flv");
    if (!cap.isOpened()) {
        std::cout << "load image error..." << std::endl;
        return -1;
    }

    unsigned FPS = cap.get(cv::CAP_PROP_FPS);
    unsigned f = static_cast<unsigned>(cap.get(cv::CAP_PROP_FOURCC));
    cv::Size size(cap.get(cv::CAP_PROP_FRAME_WIDTH), cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    char fourcc[] = {static_cast<char>(f), static_cast<char>(f >> 8), static_cast<char>(f >> 16),
                     static_cast<char>(f >> 24), '\0'};

    std::cout << fourcc << std::endl;

    cv::VideoWriter writer("../../materials/video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), FPS, size);
    if (!writer.isOpened()) {
        std::cout << "load image error..." << std::endl;
        return -1;
    }

    cv::Mat frame;
    std::string windowTitle{"Window Title"};
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        cv::imshow(windowTitle, frame);
        if (cv::waitKey(FPS) == 27) {
            break;
        }
        writer << frame;
    }

    cv::destroyWindow(windowTitle);
    return 0;
}
