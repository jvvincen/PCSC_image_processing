//
// Created by leonard on 26.12.20.
//

#ifndef TEST_FOURIER_H
#define TEST_FOURIER_H

#include "helper.h"
class fourier {
public:
    static void FFT2D(int w, int h, const double *fRe, const double *fIm, double *FRe, double *FIm, bool inverse= false);

    static void calculateAmp(int n, int m, double *fAmp, const double *fRe, const double *gIm);

    static cv::Mat draw(int n, int m, const double *f, bool shift);

    static void display_im(cv::Mat image,string title);

    static void FFT(int n, bool inverse, const double *fRe, const double *fIm, double *FRe, double *FIm, int step, double factor);
};


#endif //TEST_FOURIER_H
