#include <bits/stdc++.h>

#include "opencv2/opencv.hpp"

int main() {
    cv::Mat src, dst;
    src = cv::imread("../../materials/bkg.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    char windowTitle[40] = "input window";
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle, src);

    // filter
    cv::medianBlur(src, dst, 3);
    char dstWindowTitle[60] = "output window title";
    cv::namedWindow(dstWindowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(dstWindowTitle, dst);

    cv::Mat bImg;
    cv::bilateralFilter(src, bImg, 15, 150, 3);
    char bWindowTitle[40] = "Bilateral filter";
    cv::namedWindow(bWindowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(bWindowTitle, bImg);

    cv::Mat gImg;
    cv::GaussianBlur(src, gImg, cv::Size(15, 15), 3, 3);
    char gWindowTitle[40] = "Gaussian filter";
    cv::namedWindow(gWindowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(gWindowTitle, gImg);

    cv::Mat resultImg;
    cv::Mat kernel = (cv::Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cv::filter2D(gImg, resultImg, -1, kernel, cv::Point(-1, -1));
    cv::imshow("Gaus Window", resultImg);

    cv::waitKey(0);

    return 0;
}
