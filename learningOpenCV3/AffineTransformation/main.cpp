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
    cv::Mat src = cv::imread("../../materials/4.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cout << "load image failed..." << std::endl;
        return -1;
    }

    cv::Point2f srcTri[] = {cv::Point2f(0, 0), cv::Point2f(src.cols - 1, 0), cv::Point2f(0, src.rows - 1)};
    cv::Point2f dstTri[] = {cv::Point2f(src.cols * 0.0f, src.rows * 0.33f),
                            cv::Point2f(src.cols * 0.85f, src.rows * 0.25f),
                            cv::Point2f(src.cols * 0.15f, src.rows * 0.7f)};

    // get affine matrix
    cv::Mat warpMat = cv::getAffineTransform(srcTri, dstTri);
    cv::Mat dst, dst2;
    cv::warpAffine(src, dst, warpMat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
    for (int i = 0; i != 3; ++i) {
        cv::circle(dst, dstTri[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);
    }

    const std::string windowTitle{"Affine Transform"};
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle, dst);
    cv::waitKey();

    // get potation matrix
    for (int frame = 0;; ++frame) {
        cv::Point2f center(src.cols * 0.5f, src.rows * 0.5f);
        double angle = frame * 3 % 360;
        double scale = (cos((angle - 60) * CV_PI / 180.) + 1.05) * 0.8;

        cv::Mat rotateMat = cv::getRotationMatrix2D(center, angle, scale);
        cv::warpAffine(src, dst, rotateMat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
        const std::string windowTitleRotate{"Rotated Image"};
        cv::namedWindow(windowTitleRotate, cv::WINDOW_GUI_NORMAL);
        cv::imshow(windowTitleRotate, dst);

        if (cv::waitKey(30) >= 0) {
            break;
        }
    }

    return 0;
}
