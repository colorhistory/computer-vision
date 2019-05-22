#include <bits/stdc++.h>

#include "opencv2/opencv.hpp"

int main() {
    cv::Mat src, dst;
    src = cv::imread("/home/xiaohai/Github/computer-vision/Materials/1.jpg");
    if (!src.data) {
        printf("could not load image...\n");
        return -1;
    }

    cv::namedWindow("input image", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("input image", src);
    /*
        int cols = (src.cols - 1) * src.channels();
        int rows = src.rows;
        int offsetx = src.channels();
        dst = cv::Mat::zeros(src.size(), src.type());

        for (int row = 1; row != rows - 1; ++row) {
            const uchar *previous = src.ptr<uchar>(row - 1);
            const uchar *current = src.ptr<uchar>(row);
            const uchar *next = src.ptr<uchar>(row + 1);
            uchar *output = dst.ptr<uchar>(row);
            for (int col = offsetx; col != cols; ++col) {
                output[col] =
                    5 * current[col] - (current[col - offsetx] + current[col + offsetx] + previous[col] + next[col]);
            }
        }
    */

    double Time = cv::getTickCount();
    cv::Mat kernel = (cv::Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cv::filter2D(src, dst, src.depth(), kernel);
    double timeCounts = (cv::getTickCount() - Time) / cv::getTickFrequency();
    std::cout << "time consume " << timeCounts << std::endl;

    cv::namedWindow("kernel", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("kernel", dst);
    cv::waitKey(0);

    return 0;
}
