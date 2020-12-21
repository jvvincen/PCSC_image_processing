#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;


cv::Mat load_image(std::string image_path);

void display_im(cv::Mat);

std::vector<uchar> cv_to_vector(cv::Mat image);

std::vector<Mat> split_channels(cv::Mat image);

std::vector<std::vector<uchar>> channels_to_vectors(cv::Mat image);

cv::Mat vec_to_cv(std::vector<uchar> vec, int rows, int cols);

std::vector<int> interval(int num_in);

void print_vector(std::vector<int> vec);

#endif
