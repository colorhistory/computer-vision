#include "bits/stdc++.h"

#include "opencv2/opencv.hpp"

int main(int /* argc */, char** /* argv */) {
    cv::Mat img = cv::imread("../../materials/face2.jpg", cv::IMREAD_COLOR);

    if (img.empty()) {
        std::cout << "load image failed..." << std::endl;
        return -1;
    }

    std::string windowTitle{"Window Title"};
    cv::namedWindow(windowTitle.c_str(), cv::WINDOW_GUI_NORMAL);

    cv::imshow(windowTitle.c_str(), img);
    cv::waitKey(0);

    cv::destroyWindow(windowTitle.c_str());

    return 0;
}
