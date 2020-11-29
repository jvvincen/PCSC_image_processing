#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;


cv::Mat load_image(std::string image_path);

void display_im(cv::Mat);

std::vector<vector < vector < int>>> cv_to_vector(cv::Mat image);

std::vector<cv::Mat> split_channels(cv::Mat image);

std::vector<std::vector<uchar>> channels_to_vectors(cv::Mat image);

#endif
