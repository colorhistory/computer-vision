#include <bits/stdc++.h>

#include <opencv2/opencv.hpp>

int main() {
    cv::Mat src, gray_src;
    src = cv::imread("../../materials/face.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    cv::namedWindow("window", cv::WINDOW_GUI_NORMAL);
    cv::imshow("window", src);

    // one chanel
    cv::cvtColor(src, gray_src, cv::COLOR_BGR2GRAY);
    cv::namedWindow("grayWindow", cv::WINDOW_GUI_NORMAL);
    cv::imshow("grayWindow", gray_src);

    int height = gray_src.rows;
    int width = gray_src.cols;

    for (int row = 0; row != height; ++row) {
        for (int col = 0; col != width; ++col) {
            int gray = gray_src.at<uchar>(row, col);
            gray_src.at<uchar>(row, col) = 255 - gray;
        }
    }
    cv::namedWindow("grayWindow2", cv::WINDOW_GUI_NORMAL);
    cv::imshow("grayWindow2", gray_src);

    // three chanels
    cv::Mat dst;
    dst.create(src.size(), src.type());
    height = src.rows;
    width = src.cols;
    int nChanel = src.channels();

    for (int row = 0; row != height; ++row) {
        for (int col = 0; col != width; ++col) {
            if (nChanel == 1) {
                int gray = gray_src.at<uchar>(row, col);
            } else if (nChanel == 3) {
                int blue = src.at<cv::Vec3b>(row, col)[0];
                int green = src.at<cv::Vec3b>(row, col)[1];
                int red = src.at<cv::Vec3b>(row, col)[2];
                dst.at<cv::Vec3b>(row, col)[0] = 255 - blue;
                dst.at<cv::Vec3b>(row, col)[1] = 255 - green;
                dst.at<cv::Vec3b>(row, col)[2] = 255 - red;

                // generate gray image
                gray_src.at<uchar>(row, col) = std::min(blue, std::min(green, red));
            }
        }
    }

    cv::bitwise_not(src, dst);
    cv::namedWindow("colorWindow", cv::WINDOW_GUI_NORMAL);
    cv::imshow("colorWindow", dst);

    // generate gray image
    cv::namedWindow("generateGrayWindow", cv::WINDOW_GUI_NORMAL);
    cv::imshow("generateGrayWindow", gray_src);

    cv::waitKey(0);

    return 0;
}
