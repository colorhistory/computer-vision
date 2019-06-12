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

void sumRGB(const cv::Mat &src, cv::Mat &dst);

int main(int /* argc */, char ** /* argv */) {
    cv::Mat src;
    src = cv::imread("../../materials/face.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        return -1;
    }

    cv::Mat dst;
    sumRGB(src, dst);

    std::string windowTitle{"Window Title"};
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle, dst);

    cv::waitKey(0);

    return 0;
}

void sumRGB(const cv::Mat &src, cv::Mat &dst) {
    std::vector<cv::Mat> planes;
    cv::split(src, planes);

    cv::Mat blue = planes[0];
    cv::Mat green = planes[1];
    cv::Mat red = planes[2];
    cv::Mat s;

    cv::addWeighted(blue, 1. / 3., green, 1. / 3., 0.0, s);
    cv::addWeighted(s, 1, red, 1. / 3., 0.0, s);

    cv::threshold(s, dst, 100, 100, cv::THRESH_TRUNC);
}
