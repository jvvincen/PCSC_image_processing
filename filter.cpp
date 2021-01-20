//
// Created by leonard on 11.01.21.
//

#include "filter.h"

// Select only a portion of f to add a filter
double *filter::blur(double *f, double radius1, int H, int W, int pass, double radius2) {
    double *f_filter = new double[H * W * 3];
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++) {
            int x1 = x, y1 = y;
            x1 = (x + W / 2) % W;
            y1 = (y + H / 2) % H;
            for (int i = 0; i < 3; i++) {

                if (pow(x - W / 2, 2) + pow(y - H / 2, 2) < pow((double) H / 2 / radius1, 2) && pass == 1
                    // select only the interior of a radius1
                    || (pow(x - W / 2, 2) + pow(y - H / 2, 2) > pow((double) H / 2 / radius1, 2) ||
                        (pow(x - W / 2, 2) + pow(y - H / 2, 2) == 0)) && pass == 2
                    // select only the exterior of radius1 and the middle point to have a brighter image
                    || (pow(x - W / 2, 2) + pow(y - H / 2, 2) > pow((double) H / 2 / max(radius1, radius2), 2) &&
                        (pow(x - W / 2, 2) + pow(y - H / 2, 2) < pow((double) H / 2 / min(radius1, radius2), 2)) ||
                        (pow(x - W / 2, 2) + pow(y - H / 2, 2) == 0)) && pass == 3
                    // select only a band between radius1 and radius2 and also the middle point to have a brighter image
                    || (pow(x - W / 2, 2) + pow(y - H / 2, 2) > pow((double) H / 2 / min(radius1, radius2), 2) ||
                        (pow(x - W / 2, 2) + pow(y - H / 2, 2) < pow((double) H / 2 / max(radius1, radius2), 2))) &&
                       pass == 4
                    // select only the exterior of a band between radius1 and radius 2
                        ) {

                    f_filter[3 * W * y1 + 3 * x1 + i] = f[3 * W * y1 + 3 * x1 + i];
                } else {
                    f_filter[3 * W * y1 + 3 * x1 + i] = 0;
                }

            }
        }
    return f_filter;
}