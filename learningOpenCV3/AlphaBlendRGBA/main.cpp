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

template <typename T>
void alphaBlendRGBA(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst);

int main(int /* argc */, char ** /* argv */) {
    cv::Mat src1, src2, dst;

    src1 = cv::imread("../../materials/3.jpg", cv::IMREAD_COLOR);
    if (src1.empty()) {
        std::cout << "load image failed..." << std::endl;
        return -1;
    }
    src2 = cv::imread("../../materials/4.jpg", cv::IMREAD_COLOR);
    if (src2.empty()) {
        std::cout << "load image failed...." << std::endl;
        return -1;
    }

    std::cout << src1.type() << std::endl;
    alphaBlendRGBA<uchar>(src1, src2, dst);

    std::string dstWindowTitle{"DST Window"};
    cv::namedWindow(dstWindowTitle, cv::WINDOW_GUI_NORMAL);
    cv::imshow(dstWindowTitle, dst);

    cv::waitKey(0);

    return 0;
}

/*!
 * \brief alphaBlendRGBA
 * \param src1
 * \param src2
 * \param dst
 */
template <typename T>
void alphaBlendRGBA(const cv::Mat &src1, const cv::Mat &src2, cv::Mat &dst) {
    using VT = cv::Vec<T, 3>;
    const float alphaScale = static_cast<float>(std::numeric_limits<T>::max());
    const float invAlphaScale = static_cast<float>(1 / alphaScale);

    assert(src1.type() == src2.type());
    assert(src1.type() == cv::traits::Type<VT>::value);
    assert(src1.size() == src2.size());

    cv::Size size = src1.size();
    dst.create(size, src1.type());

    /*  cv::MatConstIterator_<VT> first1 = src1.begin<VT>();
        cv::MatConstIterator_<VT> last1 = src1.end<VT>();
        cv::MatConstIterator_<VT> last2 = src2.end<VT>();
        cv::MatIterator_<VT> dst1 = dst.begin<VT>();
    */
    auto first1 = src1.begin<VT>(), last1 = src1.end<VT>();
    auto first2 = src2.begin<VT>();
    auto dst1 = dst.begin<VT>();

    for (; first1 != last1; ++first1, ++first2, ++dst1) {
        VT pixel1 = *first1;
        VT pixel2 = *first2;

        float alpha = pixel1[3] * invAlphaScale;
        float beta = pixel2[3] * invAlphaScale;
        *dst1 = VT(cv::saturate_cast<T>(pixel1[0] * alpha + pixel2[0] * beta),
                   cv::saturate_cast<T>(pixel1[1] * alpha + pixel2[1] * beta),
                   cv::saturate_cast<T>(pixel1[2] * alpha + pixel2[2] * beta));
    }
}
