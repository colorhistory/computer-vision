#include <bits/stdc++.h>

#include "opencv2/opencv.hpp"

int main() {
    cv::Mat src1, src2, dst;
    src1 = cv::imread("../../materials/face.jpg");
    if (!src1.data) {
        std::cout << "could not load image1..." << std::endl;
        return -1;
    }

    src2 = cv::imread("../../materials/face2.jpg");
    if (!src2.data) {
        std::cout << "could not load image2..." << std::endl;
        return -1;
    }

    double alphaValue = 0.3;
    if (src1.rows == src2.rows && src1.cols == src2.cols) {
        if (src1.type() == src2.type()) {
            cv::addWeighted(src1, alphaValue, src2, 1 - alphaValue, 0.0, dst);
        }
    } else {
        std::cout << "could not blend image." << std::endl;
    }

    cv::namedWindow("src1Window", cv::WINDOW_GUI_NORMAL);
    cv::imshow("src1Window", src1);

    cv::namedWindow("src2Window", cv::WINDOW_GUI_NORMAL);
    cv::imshow("src2Window", src2);

    cv::namedWindow("dstWindow", cv::WINDOW_GUI_NORMAL);
    cv::imshow("dstWindow", dst);

    cv::waitKey(0);

    return 0;
}
