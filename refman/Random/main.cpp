#include <bits/stdc++.h>

#include "opencv2/opencv.hpp"

int main(int argc, char **argv) {
    cv::Mat src;
    src = cv::imread("../../materials/face2.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cout << "could not open image..." << std::endl;
        return -1;
    }

    char windowTitle[40] = "Window Title";
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle, src);

    cv::RNG rand(123);
    cv::Point pt1;
    cv::Point pt2;
    cv::Mat bkg = src.clone();
    for (int i = 0; i != 500; ++i) {
        pt1.x = rand.uniform(0, bkg.cols);
        pt2.x = rand.uniform(0, bkg.cols);
        pt1.y = rand.uniform(0, bkg.rows);
        pt2.y = rand.uniform(0, bkg.rows);
        cv::Scalar color = cv::Scalar(rand.uniform(0, 10), rand.uniform(0, 10), rand.uniform(0, 10));
        cv::line(bkg, pt1, pt1, color, 1, 8);
        cv::line(bkg, cv::Point(pt1.x + 1, pt1.y + 1), cv::Point(pt1.x + 1, pt1.y), color, 1, 8);
    }

    char windowTitle2[40] = "Window Title2";
    cv::namedWindow(windowTitle2, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle2, bkg);
    cv::imwrite("../../materials/bkg.jpg", bkg);

    cv::waitKey(0);

    return 0;
}
