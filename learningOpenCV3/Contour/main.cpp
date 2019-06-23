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

cv::Mat gGrayImg, gBinaryImg;
int gThresh = 100;

void onTrackBar(int gThresh, void*) {
    cv::threshold(gGrayImg, gBinaryImg, gThresh, 255, cv::THRESH_BINARY);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(gBinaryImg, contours, cv::noArray(), cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    gBinaryImg = cv::Scalar::all(0);

    cv::drawContours(gBinaryImg, contours, -1, cv::Scalar::all(255));
    cv::imshow("Contours", gBinaryImg);

    cv::imwrite("contours.jpg", gBinaryImg);
}

int main(int /* argc */, char** /* argv */) {
    gGrayImg = cv::imread("../../materials/face.jpg", cv::IMREAD_GRAYSCALE);
    if (gGrayImg.empty()) {
        std::cerr << "load image error..." << std::endl;
        return -1;
    }

    cv::namedWindow("Contours", cv::WINDOW_GUI_NORMAL);

    cv::createTrackbar("Threshold", "Contours", &gThresh, 255, onTrackBar);
    onTrackBar(0, 0);

    cv::waitKey();

    return 0;
}
