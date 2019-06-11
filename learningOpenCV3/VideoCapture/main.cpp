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
    cv::VideoCapture cap("../../materials/clock.flv");
    if (!cap.isOpened()) {
        std::cout << "load image error..." << std::endl;
        return -1;
    }

    unsigned FPS = cap.get(cv::CAP_PROP_FPS);
    unsigned f = static_cast<unsigned>(cap.get(cv::CAP_PROP_FOURCC));

    char fourcc[] = {static_cast<char>(f), static_cast<char>(f >> 8), static_cast<char>(f >> 16),
                     static_cast<char>(f >> 24), '\0'};

    std::cout << fourcc << std::endl;

    cv::VideoWriter writer("../../materials/video.flv", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), FPS,
                           cv::Size(640, 480));
    if (!writer.isOpened()) {
        std::cout << "load image error..." << std::endl;
        return -1;
    }

    cv::Mat frame;
    std::string windowTitle{"Window Title"};
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);

    while (true) {
        if (cap.read(frame)) {
            cv::imshow(windowTitle, frame);
            if (cv::waitKey(FPS) == 27) {
                break;
            }
            writer.write(frame);
        }
    }

    cv::destroyWindow(windowTitle);
    return 0;
}
