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
    cv::VideoCapture cap;
    cap.open("../../materials/video.flv");
    if (!cap.isOpened()) {
        std::cout << "load video error..." << std::endl;
        return -1;
    }

    cv::Point pt1(20, 20);
    cv::Point pt2(100, 100);
    int maxBuffer;
    cv::Mat srcImage;
    std::ofstream b("blines.csv"), g("glines.csv"), r("rlines.csv");

    std::string windowTitle{"Window Title"};
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);
    for (;;) {
        cap >> srcImage;
        if (!srcImage.empty()) {
            break;
        }

        cv::LineIterator it(srcImage, pt1, pt2, 8);
        for (int j = 0; j != it.count; ++j, ++it) {
            b << static_cast<int>((*it)[0]) << ", ";
            g << static_cast<int>((*it)[0]) << ", ";
            r << static_cast<int>((*it)[0]) << ", ";
            (*it)[2] = 255;
        }
        cv::imshow(windowTitle, srcImage);
        int c = cv::waitKey(10);
        b << std::endl;
        g << std::endl;
        r << std::endl;
    }

    b << std::endl;
    g << std::endl;
    r << std::endl;
    b.close();
    g.close();
    r.close();

    return 0;
}
