#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <cmath>
#include <complex>
using namespace std;



cv::Mat load_image(std::string image_path);

void display_im(cv::Mat);

std::vector<vector < vector < double>>> cv_to_vector(cv::Mat image);

void FFT2D(int w, int h, bool inverse, const double *gRe, const double *gIm, double *GRe, double *GIm);
void FFTbis(vector<double> vect_in, vector<complex<double>> vect_out, int N);
void draw(int n, int m, const double *g);
void calculateAmp(int n, int m, double *gAmp, const double *gRe, const double *gIm);
std::vector<cv::Mat> split_channels(cv::Mat image);

std::vector<std::vector<uchar>> channels_to_vectors(cv::Mat image);

#endif
