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
    cv::RNG rng = cv::theRNG();

    std::cout << "An integer:      " << static_cast<int>(rng) << std::endl;
    std::cout << "Another integer: " << int(rng) << std::endl;

    std::cout << "A float:         " << static_cast<float>(rng) << std::endl;
    std::cout << "Another float:   " << float(rng) << std::endl;

    return 0;
}
