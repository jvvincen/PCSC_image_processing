//
// Created by leonard on 11.01.21.
//

#ifndef TEST_FILTER_H
#define TEST_FILTER_H
#include "helper.h"
#include "fourier.h"

class filter {
public:
   static double* blur(double *f,double divided_radius,int H,int W,int pass,double radius2=0);
};


#endif //TEST_FILTER_H
