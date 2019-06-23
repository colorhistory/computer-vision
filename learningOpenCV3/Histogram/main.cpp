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
    cv::Mat src = cv::imread("../../materials/face2.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cerr << "load image error..." << std::endl;
        return -1;
    }

    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

    float hRanges[] = {0, 256};
    float sRanges[] = {0, 256};
    const float* ranges[] = {hRanges, sRanges};
    int histSize[] = {30, 32};
    int ch[] = {0, 1};

    cv::Mat hist;

    // compute the histogram
    cv::calcHist(&hsv, 1, ch, cv::noArray(), hist, 2, histSize, ranges, true);
    cv::normalize(hist, hist, 0, 255, cv::NORM_MINMAX);

    int scale = 10;
    cv::Mat histImg(histSize[0] * scale, histSize[1] * scale, CV_8SC3);

    // draw histogram
    for (int h = 0; h != histSize[0]; ++h) {
        for (int s = 0; s != histSize[1]; ++s) {
            float val = hist.at<float>(h, s);
            cv::rectangle(histImg, cv::Rect(h * scale, s * scale, scale, scale), cv::Scalar::all(val), -1);
        }
    }

    const std::string srcWindowTitle{"Src Window"};
    const std::string histWindowTitle{"Hist Window"};
    cv::namedWindow(srcWindowTitle, cv::WINDOW_GUI_NORMAL);
    cv::namedWindow(histWindowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(srcWindowTitle, src);
    cv::imshow(histWindowTitle, histImg);

    cv::waitKey();

    return 0;
}
