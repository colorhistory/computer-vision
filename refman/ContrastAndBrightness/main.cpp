#include <bits/stdc++.h>

#include "opencv2/opencv.hpp"

int main(int argc, char **argv) {
    cv::Mat src, dst;
    src = cv::imread("../../materials/2.jpg", cv::IMREAD_COLOR);
    if (!src.data) {
        std::cout << "could not load images..." << std::endl;
        return -1;
    }

    cv::namedWindow("srcWindow", cv::WINDOW_GUI_NORMAL);
    cv::imshow("srcWindow", src);

    // contrast nd brightness changes
    //    g(i, j) = alpha * f(i, j) + beta
    int height = src.rows;
    int width = src.cols;
    dst = cv::Mat::zeros(src.size(), src.type());
    float alpha = 2.0, beta = 10;

    cv::Mat img;
    src.convertTo(img, CV_32F);
    for (int row = 0; row != height; ++row) {
        for (int col = 0; col != width; ++col) {
            if (src.channels() == 3) {
                float blue = src.at<cv::Vec3b>(row, col)[0];
                float green = src.at<cv::Vec3b>(row, col)[1];
                float red = src.at<cv::Vec3b>(row, col)[2];

                dst.at<cv::Vec3b>(row, col)[0] = cv::saturate_cast<uchar>(alpha * blue + beta);
                dst.at<cv::Vec3b>(row, col)[1] = cv::saturate_cast<uchar>(alpha * green + beta);
                dst.at<cv::Vec3b>(row, col)[2] = cv::saturate_cast<uchar>(alpha * red + beta);

            } else if (src.channels() == 1) {
                float value = src.at<uchar>(row, col);
                dst.at<uchar>(row, col) = cv::saturate_cast<uchar>(alpha * value + beta);
            }
        }
    }
    char *windowTitle = "dst Window";
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle, dst);

    // float
    for (int row = 0; row != height; ++row) {
        for (int col = 0; col != width; ++col) {
            if (src.channels() == 3) {
                float blue = img.at<cv::Vec3f>(row, col)[0];
                float green = img.at<cv::Vec3f>(row, col)[1];
                float red = img.at<cv::Vec3f>(row, col)[2];

                dst.at<cv::Vec3b>(row, col)[0] = cv::saturate_cast<uchar>(alpha * blue + beta);
                dst.at<cv::Vec3b>(row, col)[1] = cv::saturate_cast<uchar>(alpha * green + beta);
                dst.at<cv::Vec3b>(row, col)[2] = cv::saturate_cast<uchar>(alpha * red + beta);

            } else if (src.channels() == 1) {
                float value = src.at<uchar>(row, col);
                dst.at<uchar>(row, col) = cv::saturate_cast<uchar>(alpha * value + beta);
            }
        }
    }
    windowTitle = "float image Window";
    cv::namedWindow(windowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(windowTitle, dst);

    cv::waitKey(0);

    return 0;
}
