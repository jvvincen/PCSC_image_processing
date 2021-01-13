//
// Created by leonard on 26.12.20.
//

#ifndef TEST_IMAGE_H
#define TEST_IMAGE_H


#include "helper.h"
#include "fourier.h"
#include "filter.h"

class image {
public:
    static void display_fourier(cv::Mat image, string title);

    static void display_blur(cv::Mat image, double divided_radius, int filter, double radius2=0);

    static cv::Mat create_sin_image(int size);

    static void choose_filter(cv::Mat image);
};


#endif //TEST_IMAGE_H
