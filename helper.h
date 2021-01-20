//
// Created by leonard on 26.12.20.
//

#ifndef TEST_HELPER_H
#define TEST_HELPER_H
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
class helper {

public:
    static vector<vector<vector<double>>> cv_to_vector(cv::Mat image);

    static cv::Mat load_image(string image_path);

    /*!
     * @brief transform an image Mat into an array
     * @param image
     * @return the pointer in which the array of the image is stored
     */
    static double *cv_to_pointer(cv::Mat image);

    /*!
     * @brief Load and transform an image to a square image of a size of power of 2.
     * To fill the square image, the rest of the values will be set to zero.
     * @param image_path local path where the image is saved
     * @return a square image Mat
     */
    static cv::Mat load_square_image(string image_path);

};


#endif //TEST_HELPER_H
