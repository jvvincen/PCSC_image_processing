//
// Created by leonard on 26.12.20.
//

#ifndef TEST_FOURIER_H
#define TEST_FOURIER_H

#include "helper.h"

class fourier {
public:
    /*!
     * 2D Fast Fourier transform that calls the 1D FFT for each row and each column
     * @param w weight of the image
     * @param h height of the image
     * @param fRe input of the real part of the image
     * @param fIm input of the imaginary part of the image
     * @param FRe output of the real part of the transformed image
     * @param FIm output of the imaginary part of the transformed image
     * @param inverse if it calculate the inverse of fft or not
     */
    static void FFT2D(int w, int h, const double *fRe, const double *fIm, double *FRe, double *FIm, bool inverse = false);

    /*!
     * @brief Calculates the amplitude of a complex number Amp = sqrt(fRe²+fIm²)
     * @param w weight of the image
     * @param h height of the image
     * @param fAmp output of the calculated amplitude
     * @param fRe input of the real part of the image
     * @param fIm input of the imaginary part of the image
     */
    static void calculateAmp(int w, int h, double *fAmp, const double *fRe, const double *gIm);

    /*!
    * @brief Create an image Mat from an array of size (w * h * 3)
    * @param w weight of the image
    * @param h height of the image
    * @param f array to be transformed to an image
    * @param shift true if the image to create is a fourier transform
    * @return image Mat
    */
    static cv::Mat draw(int w, int h, const double *f, bool shift);

    /*!
    * @brief Print a Mat image with a giver title
    * @param image
    * @param title
    */
    static void display_im(cv::Mat image, string title);

    /*!
     * @brief 1D Fast Fourier transform that work non recursively
     * @param n size of the array to be transformed
     * @param inverse if it calculate the inverse of fft or not
     * @param fRe input of the real part of the array
     * @param fIm input of the imaginary part of the array
     * @param FRe output of the real part of the transformed array
     * @param FIm output of the imaginary part of the transformed array
     * @param step the row size to work on a column
     * @param factor the value to divide the result with
     */
    static void
    FFT(int n, bool inverse, const double *fRe, const double *fIm, double *FRe, double *FIm, int step, double factor);

};


#endif //TEST_FOURIER_H
