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
    using Mat = cv::Mat;
    Mat src, dst;
    src = cv::imread("../../materials/face2.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cerr << "load image error..." << std::endl;
        return -1;
    }

    cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
    const std::string srcWindowTitle{"Src Window"};
    const std::string dstWindowTitle{"Dst Window"};
    cv::namedWindow(srcWindowTitle, cv::WINDOW_GUI_NORMAL);
    cv::namedWindow(dstWindowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(srcWindowTitle, src);

    cv::equalizeHist(src, dst);
    cv::imshow(dstWindowTitle, dst);

    cv::waitKey();

    return 0;
}
