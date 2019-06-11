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
    cv::Mat imgRGB, imgGRY, imgCNY, imgPYR, imgPYR2;

    imgRGB = cv::imread("../../materials/2.jpg", cv::IMREAD_COLOR);
    if (imgRGB.empty()) {
        std::cout << "load image failed..." << std::endl;
        return -1;
    }

    std::cout << "Source Image Channels are: " << imgRGB.channels() << std::endl;
    std::cout << "Source Type is: " << imgRGB.type() << std::endl;

    cv::cvtColor(imgRGB, imgGRY, cv::COLOR_BGR2GRAY);
    cv::pyrDown(imgGRY, imgPYR);
    cv::pyrDown(imgPYR, imgPYR2);
    cv::Canny(imgPYR2, imgCNY, 10, 100, 3, true);

    int x = 20, y = 24;
    cv::Vec3b intensity = imgRGB.at<cv::Vec3b>(x, y);

    uchar blue = static_cast<uchar>(intensity[0]);
    uchar green = static_cast<uchar>(intensity[1]);
    uchar red = static_cast<uchar>(intensity[2]);

    std::cout << "At (x, y) = (" << x << ", " << y << "): (B, G, R) = (" << blue << ", " << green << ", " << red << ")"
              << std::endl;
    std::cout << "Gray pixel thers is: " << imgGRY.at<uchar>(x, y) << std::endl;

    x = x / 4;
    y = y / 4;

    std::cout << "Pyramid pixel there is: " << imgPYR2.at<uchar>(x, y) << std::endl;

    imgCNY.at<uchar>(x, y) = 128;

    std::string grayWindowTitle{"Gray Window"};
    cv::namedWindow(grayWindowTitle.c_str(), cv::WINDOW_GUI_NORMAL);
    cv::imshow(grayWindowTitle.c_str(), imgGRY);

    std::string cannyWindowTiitle{"Canny Window"};
    cv::namedWindow(grayWindowTitle.c_str(), cv::WINDOW_GUI_NORMAL);
    cv::imshow(cannyWindowTiitle.c_str(), imgPYR2);

    cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}
