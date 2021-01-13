//
// Created by leonard on 26.12.20.
//

#ifndef TEST_HELPER_H
#define TEST_HELPER_H
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <cmath>
#include <complex>
using namespace std;
class helper {

public:
    static vector<vector<vector<double>>> cv_to_vector(cv::Mat image);

    static cv::Mat load_image(string image_path);

    static double *cv_to_pointer(cv::Mat image);

    static cv::Mat load_square_image(string image_path);

};


#endif //TEST_HELPER_H
