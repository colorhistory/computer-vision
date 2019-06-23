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
        std::cerr << "load image failed..." << std::endl;
        return -1;
    }

    using Point2f = cv::Point2f;
    Point2f srcQuad[] = {Point2f(0.0, 0.0), Point2f(src.cols - 1, 0), Point2f(src.cols - 1, src.rows - 1),
                         Point2f(0, src.rows - 1)};
    Point2f dstQuad[] = {Point2f(src.cols * 0.05f, src.rows * 0.33f), Point2f(src.cols * 0.9f, src.rows * 0.25f),
                         Point2f(src.cols * 0.8f, src.rows * 0.9f), Point2f(src.cols * 0.2f, src.rows * 0.7f)};

    // get perspective matrix
    cv::Mat warpMat = cv::getPerspectiveTransform(srcQuad, dstQuad);
    cv::Mat dst;
    cv::warpPerspective(src, dst, warpMat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

    for (int i = 0; i != 4; ++i) {
        cv::circle(dst, dstQuad[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);
    }

    const std::string windowTitle{"Perspective Transform"};
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle, dst);
    cv::waitKey();

    return 0;
}
