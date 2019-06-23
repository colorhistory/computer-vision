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
    cv::Mat src = cv::imread("../../materials/face2.jpg", cv::IMREAD_GRAYSCALE);
    if (src.empty()) {
        std::cerr << "load image error..." << std::endl;
        return -1;
    }

    cv::Size patchSize(200, 600);
    cv::Point topleft(src.cols / 100, src.rows / 100);
    cv::Rect roi(topleft.x, topleft.y, patchSize.width, patchSize.height);
    cv::Mat dst = src(roi);

    int dft_M = cv::getOptimalDFTSize(src.rows + dst.rows - 1);
    int dft_N = cv::getOptimalDFTSize(src.cols + dst.cols - 1);

    cv::Mat dft_A = cv::Mat::zeros(dft_M, dft_N, CV_32F);
    cv::Mat dft_B = cv::Mat::zeros(dft_M, dft_N, CV_32F);

    cv::Mat dft_A_part = dft_A(cv::Rect(0, 0, src.cols, src.rows));
    cv::Mat dft_B_part = dft_B(cv::Rect(0, 0, dst.cols, dst.cols));

    src.convertTo(dft_A_part, dft_A_part.type(), 1, -cv::mean(src)[0]);
    dst.convertTo(dft_B_part, dft_B_part.type(), 1, -cv::mean(dst)[0]);

    cv::dft(dft_A, dft_A, 0, src.rows);
    cv::dft(dft_B, dft_B, 0, dst.rows);

    //
    cv::mulSpectrums(dft_A, dft_B, dft_A, 0, true);
    cv::idft(dft_A, dft_A, CV_HAL_DFT_SCALE, src.rows + dst.rows - 1);

    cv::Mat corr = dft_A(cv::Rect(0, 0, src.cols + dst.cols - 1, src.rows + dst.rows - 1));
    cv::normalize(corr, corr, 0, 1, cv::NORM_MINMAX, corr.type());
    cv::pow(corr, 3.0, corr);

    dst ^= cv::Scalar::all(255);

    const std::string srcWindow{"Src Window"};
    const std::string dstWindow{"Dst Window"};
    cv::namedWindow(srcWindow, cv::WINDOW_GUI_NORMAL);
    cv::namedWindow(dstWindow, cv::WINDOW_GUI_NORMAL);
    cv::imshow(srcWindow, src);
    cv::imshow(dstWindow, dst);

    cv::waitKey(0);

    return 0;
}
