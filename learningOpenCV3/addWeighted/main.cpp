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
    cv::Mat src1, src2, dst;
    src1 = cv::imread("../../materials/4.jpg", cv::IMREAD_COLOR);
    src2 = cv::imread("../../materials/5.jpg", cv::IMREAD_COLOR);
    if (src1.empty() || src2.empty()) {
        std::cout << "load image error..." << std::endl;
        return -1;
    }

    double alpha = 0.7;
    double beta = 0.3;
    double gamma = 0.0;

    int width = 300;
    int height = 300;

    cv::Mat roi1(src1, cv::Rect(100, 100, width, height));
    cv::Mat roi2(src2, cv::Rect(300, 300, width, height));

    cv::addWeighted(roi1, alpha, roi2, beta, gamma, dst);

    std::string dstWindowTitle{"Dst Window"};
    cv::namedWindow(dstWindowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(dstWindowTitle, dst);

    cv::waitKey(0);

    return 0;
}
