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

void GaussianBlur(const cv::Mat &src);

int main(int /* argc */, char ** /* argv */) {
    cv::Mat src = cv::imread("../../materials/face2.jpg", cv::IMREAD_COLOR);

    GaussianBlur(src);

    return 0;
}

void GaussianBlur(const cv::Mat &src) {
    std::string inputWindowTitle{"Input Window Title"};
    cv::namedWindow(inputWindowTitle.c_str(), cv::WINDOW_GUI_NORMAL);
    std::string outputWindowTitle{"Output Window Title"};
    cv::namedWindow(outputWindowTitle.c_str(), cv::WINDOW_GUI_NORMAL);

    cv::imshow(inputWindowTitle.c_str(), src);

    cv::Mat dst(src.size(), src.type());

    cv::GaussianBlur(src, dst, cv::Size(5, 5), 3, 3);

    cv::imshow(outputWindowTitle.c_str(), dst);

    cv::waitKey(0);
}
