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
    cv::VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened()) {
        std::cout << "open camera failed..." << std::endl;
        return -1;
    }

    const double FPS = cap.get(cv::CAP_PROP_FPS);
    const cv::Size size(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)),
                        static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::VideoWriter writer;
    writer.open("video.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), FPS, size);
    if (!writer.isOpened()) {
        std::cout << "open file error..." << std::endl;
        return -1;
    }

    std::string srcWindowTitle{"SRC Window"};
    cv::namedWindow(srcWindowTitle, cv::WINDOW_GUI_NORMAL);
    std::string logPolarWindowTitle{"LogPolar Window"};
    cv::namedWindow(logPolarWindowTitle, cv::WINDOW_GUI_NORMAL);

    cv::Mat imgLogPolar, imgSrc;
    while (true) {
        cap >> imgSrc;
        if (imgSrc.empty()) {
            break;
        }
        cv::imshow(srcWindowTitle, imgSrc);

        cv::logPolar(imgSrc, imgLogPolar, cv::Point2f(imgSrc.cols / 2, imgSrc.rows / 2), 20, cv::WARP_FILL_OUTLIERS);

        cv::imshow("LogPolar", imgLogPolar);
        writer << imgLogPolar;

        if (static_cast<char>(cv::waitKey(10)) == 27) {
            break;
        }
    }

    cap.release();
    writer.release();

    cv::destroyAllWindows();

    return 0;
}
