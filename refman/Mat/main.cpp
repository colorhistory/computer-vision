#include <bits/stdc++.h>

#include "opencv2/opencv.hpp"

int main() {
    cv::Mat src;
    src = cv::imread("/home/xiaohai/Github/computer-vision/Materials/1.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        printf("could not load image...\n");
        return -1;
    }

    /* cv::Mat dst;
    dst = cv::Mat(src.size(), src.type());
    dst = cv::Scalar(124, 3, 35);
    */

    /* cv::Mat dst;
     src.copyTo(dst);
     */

    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    std::cout << src.channels() << "   " << dst.channels() << std::endl;

    cv::namedWindow("window", cv::WINDOW_GUI_NORMAL);
    cv::imshow("window", dst);

    cv::waitKey(0);
    return 0;
}
