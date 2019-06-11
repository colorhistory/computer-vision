/****************************************************************************
**
** Copyright (C) 2019 Xiaohai <xiaohaidotpro@outlook.com>.
** Contact: http://xiaohai.pro
**
** This file is part of learningOpenCV3
**
**
****************************************************************************/

#include "bits/stdc++.h"

#include "opencv2/opencv.hpp"

int main(int /* argc */, char** /* argv */) {
    cv::Mat src, dst;
    src = cv::imread("../../materials/face2.jpg", cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cout << "load image failed..." << std::endl;
        return -1;
    }
    std::string inputWindowTitle{"Input Window Title"};
    cv::namedWindow(inputWindowTitle.c_str(), cv::WINDOW_GUI_NORMAL);
    cv::imshow(inputWindowTitle.c_str(), src);

    cv::pyrDown(src, dst);
    std::string outputWindowTitle{"Output Window Title"};
    cv::namedWindow(outputWindowTitle.c_str(), cv::WINDOW_GUI_NORMAL);
    cv::imshow(outputWindowTitle.c_str(), dst);

    cv::waitKey(0);

    return 0;
}
