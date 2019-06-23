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
    cv::Mat src = cv::imread("../../materials/face.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cerr << "load image failded..." << std::endl;
        return -1;
    }

    double M = 0.5;
    cv::Mat dst(src.size(), src.type());
    cv::Mat src2(src.size(), src.type());

    cv::logPolar(src, dst, cv::Point2f(src.cols * 0.5f, src.rows * 0.5f), M, cv::INTER_LINEAR | cv::WARP_FILL_OUTLIERS);
    cv::logPolar(dst, src2, cv::Point2f(src.cols * 0.5f, src.rows * 0.5f), M, cv::INTER_LINEAR | cv::WARP_INVERSE_MAP);

    const std::string windowTitle{"Window Log Polar"};
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle, dst);
    const std::string windowTitle2{"Window Inverse Log Polar"};
    cv::namedWindow(windowTitle2, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle2, src2);

    cv::waitKey();

    return 0;
}
