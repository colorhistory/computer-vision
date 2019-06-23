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
    std::vector<cv::Mat> src(5);
    cv::Mat tmp;
    int i = 0;

    tmp = cv::imread("../../materials/face.jpg", cv::IMREAD_COLOR);
    if (tmp.empty()) {
        std::cerr << "load image error..." << std::endl;
        return -1;
    }

    cv::Size size = tmp.size();
    int width = size.width;
    int height = size.height;
    int haftHeight = height / 2;

    std::cout << "Getting size [[" << tmp.cols << "] [" << tmp.rows << "]]\n" << std::endl;
    std::cout << "Got size (w, h): (" << size.width << ", " << size.height << ")" << std::endl;

    src[0] = cv::Mat(cv::Size(width, haftHeight), CV_8UC3);
    src[1] = cv::Mat(cv::Size(width, haftHeight), CV_8UC3);

    // Divide the first image
    cv::Mat_<cv::Vec3b>::iterator tmpIter = tmp.begin<cv::Vec3b>();

    // top half
    cv::Mat_<cv::Vec3b>::iterator s0Iter = src[0].begin<cv::Vec3b>();
    for (i = 0; i != width * haftHeight; ++i, ++tmpIter, ++s0Iter) {
        *s0Iter = *tmpIter;
    }

    // bottom half
    cv::Mat_<cv::Vec3b>::iterator s1Iter = src[1].begin<cv::Vec3b>();
    for (i = 0; i != width * haftHeight; ++i, ++tmpIter, ++s1Iter) {
        *s1Iter = *tmpIter;
    }

    // load other images
    src[2] = cv::imread("../../materials/face.jpg", cv::IMREAD_COLOR);
    src[3] = cv::imread("../../materials/face.jpg", cv::IMREAD_COLOR);
    src[4] = cv::imread("../../materials/face.jpg", cv::IMREAD_COLOR);

    if (src[2].empty() || src[3].empty() || src[4].empty()) {
        std::cout << "load image error..." << std::endl;
        return -1;
    }

    std::vector<cv::Mat> hsv(5), hist(5), histImg(5);
    int hBins = 8;
    int sBins = 8;
    int histSize[] = {hBins, sBins};
    int ch[] = {0, 1};
    float hRanges[] = {0, 180};
    float sRanges[] = {0, 255};
    const float* range[] = {hRanges, sRanges};
    int scale = 10;

    for (i = 0; i != 5; ++i) {
        cv::cvtColor(src[i], hsv[i], cv::COLOR_BGR2HSV);
        cv::calcHist(&hsv[i], 1, ch, cv::noArray(), hist[i], 2, histSize, range, true);
        cv::normalize(hist[i], hist[i], 0, 255, cv::NORM_MINMAX);
        histImg[i] = cv::Mat::zeros(histSize[0] * scale, histSize[1] * scale, CV_8UC3);

        for (int h = 0; h != histSize[0]; ++h) {
            for (int s = 0; s != histSize[1]; ++s) {
                float hval = hist[i].at<float>(h, s);
                cv::rectangle(histImg[i], cv::Rect(h * scale, s * scale, scale, scale), cv::Scalar::all(hval), -1);
            }
        }
    }

    const std::string windowSource0 = "Source 0";
    cv::namedWindow(windowSource0, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowSource0, src[0]);
    const std::string windowHSHist0 = "HS Histogram0";
    cv::namedWindow(windowHSHist0, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowHSHist0, histImg[0]);

    const std::string windowSource1 = "Source 1";
    cv::namedWindow(windowSource1, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowSource1, src[1]);
    const std::string windowHSHist1 = "HS Histogram1";
    cv::namedWindow(windowHSHist1, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowHSHist1, histImg[1]);

    const std::string windowSource2 = "Source 2";
    cv::namedWindow(windowSource2, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowSource2, src[2]);
    const std::string windowHSHist2 = "HS Histogram2";
    cv::namedWindow(windowHSHist2, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowHSHist2, histImg[2]);

    const std::string windowSource3 = "Source 3";
    cv::namedWindow(windowSource3, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowSource3, src[3]);
    const std::string windowHSHist3 = "HS Histogram3";
    cv::namedWindow(windowHSHist3, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowHSHist3, histImg[3]);

    const std::string windowSource4 = "Source 4";
    cv::namedWindow(windowSource4, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowSource4, src[4]);
    const std::string windowHSHist4 = "HS Histogram4";
    cv::namedWindow(windowHSHist4, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowHSHist4, histImg[4]);

    for (i = 1; i != 5; ++i) {
        std::cout << "Hist[0] vs Hist[" << i << "]: " << std::endl;
        for (int j = 0; j != 4; ++j) {
            std::cout << "method[" << j << "]: " << cv::compareHist(hist[0], hist[i], j) << " ";
        }
        std::cout << std::endl;
    }

    //
    std::vector<cv::Mat> sig(5);
    std::cout << "\nEMD: " << std::endl;

    for (i = 0; i != 5; ++i) {
        std::vector<cv::Vec3f> sigv;

        cv::normalize(hist[i], hist[i], 1, 0, cv::NORM_L1);
        for (int h = 0; h != hBins; ++h) {
            for (int s = 0; s != sBins; ++s) {
                float binVal = hist[i].at<float>(h, s);
                if (binVal != 0) {
                    sigv.push_back(cv::Vec3f(binVal, static_cast<float>(h), static_cast<float>(s)));
                }
            }
        }

        sig[i] = cv::Mat(sigv).clone().reshape(1);
        if (i > 0) {
            std::cout << "Hist[0] vs Hist [" << i << "]: " << cv::EMD(sig[0], sig[i], cv::DIST_L2) << std::endl;
        }
    }

    cv::waitKey(0);

    return 0;
}
