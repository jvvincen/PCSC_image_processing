//
// Created by leonard on 11.01.21.
//

#ifndef TEST_FILTER_H
#define TEST_FILTER_H
#include "helper.h"
#include "fourier.h"

class filter {
public:
    /*!
     * @brief add a filter to an image by selecting only a portion of the transformed image
     * @param f array of fourier transformed image
     * @param radius1 factor which the radius will be divided by
     * @param W weight of the image
     * @param H height of the image
     * @param pass filter type (1 = low pass filter ; 2 = high pass filter ; 3 = select band pass)
     * @param radius2 factor which the 2nd radius will by divided by (only used for filer type 3 and 4), by default 0
     * @return array of same size in which the unselected value are 0
     */
   static double* blur(double *f, double radius1, int H, int W, int pass, double radius2=0);
};


#endif //TEST_FILTER_H
