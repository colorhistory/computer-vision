#include <bits/stdc++.h>

#include "opencv2/opencv.hpp"

int main() {
    cv::Mat img = cv::imread("/home/xiaohai/Github/computer-vision/Materials/1.jpg", cv::IMREAD_COLOR);
    if (img.empty()) {
        printf("could not load image...\n");
        return -1;
    }

    cv::namedWindow("window", cv::WINDOW_AUTOSIZE);
    cv::imshow("window", img);

    cv::Mat outputImg;
    cv::namedWindow("window1", cv::WINDOW_AUTOSIZE);
    cv::cvtColor(img, outputImg, cv::COLOR_BGR2GRAY);
    cv::imshow("window1", outputImg);

    // save image
    cv::imwrite("/home/xiaohai/Github/computer-vision/Materials/test.jpg", outputImg);

    cv::waitKey(0);

    return 0;
}
