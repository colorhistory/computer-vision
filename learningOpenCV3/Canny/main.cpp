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
    cv::Mat imgRGB, imgGRY, imgCNY;

    imgRGB = cv::imread("../../materials/face2.jpg", cv::IMREAD_COLOR);
    if (imgRGB.empty()) {
        std::cout << "load image failed..." << std::endl;
        return -1;
    }

    std::string inputWindowTitle{"Input Window Title"};
    cv::namedWindow(inputWindowTitle.c_str(), cv::WINDOW_GUI_NORMAL);
    cv::imshow(inputWindowTitle.c_str(), imgRGB);

    cv::cvtColor(imgRGB, imgGRY, cv::COLOR_BGR2GRAY);
    std::string grayWindowTitle{"Gray Window Title"};
    cv::namedWindow(grayWindowTitle.c_str(), cv::WINDOW_GUI_NORMAL);
    cv::imshow(grayWindowTitle.c_str(), imgGRY);

    cv::Canny(imgGRY, imgCNY, 10, 100, 3, true);
    std::string cannyWindowTitle{"Canny Window"};
    cv::namedWindow(cannyWindowTitle.c_str(), cv::WINDOW_GUI_NORMAL);
    cv::imshow(cannyWindowTitle.c_str(), imgCNY);

    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}
