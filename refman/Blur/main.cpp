#include <bits/stdc++.h>

#include "opencv2/opencv.hpp"

using namespace std;

int main() {
    cv::Mat src, dst;
    src = cv::imread("../../materials/face2.jpg");
    if (src.empty()) {
        std::cout << "could not load image..." << std::endl;
        return -1;
    }

    char srcWindow[20] = "input image";
    cv::namedWindow(srcWindow, cv::WINDOW_GUI_NORMAL);
    cv::imshow(srcWindow, src);

    cv::blur(src, dst, cv::Size(5, 5), cv::Point(-1, 1));
    char dstWindow[20] = "output image";
    cv::namedWindow(dstWindow, cv::WINDOW_GUI_NORMAL);
    cv::imshow(dstWindow, dst);

    // Gaus blur
    cv::Mat gausDst;
    gausDst.create(src.size(), src.type());
    cv::GaussianBlur(src, gausDst, cv::Size(5, 5), 11, 11);
    char gausBlueWindow[40] = "gaus blur window";
    cv::namedWindow(gausBlueWindow, cv::WINDOW_GUI_NORMAL);
    cv::imshow(gausBlueWindow, gausDst);
    cv::waitKey(0);

    return 0;
}
