//
// Created by leonard on 26.12.20.
//

#include "fourier.h"

void fourier::display_im(cv::Mat image,string title)
{
    imshow(title, image);
    int k = cv::waitKey(1000);
}

// 1D Fast Fourier transform that work non recursively.
void fourier::FFT(int n, bool inverse, const double *fRe, const double *fIm, double *FRe, double *FIm, int step, double factor)
{
    int h = log2(n);

    //Bit reversal
    FRe[(n - 1) * step] = fRe[(n - 1) * step];
    FIm[(n - 1) * step] = fIm[(n - 1) * step];
    int j = 0;
    for(int i = 0; i < n - 1; i++)
    {
        FRe[i * step] = fRe[j * step];
        FIm[i * step] = fIm[j * step];
        int k = n / 2;
        while(k <= j)
        {
            j -= k;
            k /= 2;
        }
        j += k;
    }
    // Calculate the FFT
    double ca = -1.0;
    double sa = 0.0;
    int l1 = 1, l2 = 1;
    for(int l = 0; l < h; l++)
    {
        l1 = l2;
        l2 *= 2;
        double u1 = 1.0;
        double u2 = 0.0;
        for(int j = 0; j < l1; j++)
        {
            for(int i = j; i < n; i += l2)
            {
                int i1 = i + l1;
                double t1 = u1 * FRe[i1 * step] - u2 * FIm[i1 * step];
                double t2 = u1 * FIm[i1 * step] + u2 * FRe[i1 * step];
                FRe[i1 * step] = FRe[i * step] - t1;
                FIm[i1 * step] = FIm[i * step] - t2;
                FRe[i * step] += t1;
                FIm[i * step] += t2;
            }
            double z =  u1 * ca - u2 * sa;
            u2 = u1 * sa + u2 * ca;
            u1 = z;
        }
        sa = sqrt((1.0 - ca) / 2.0);
        if(!inverse) sa =- sa;
        ca = sqrt((1.0 + ca) / 2.0);
    }
    // Divide through the factor
    for(int i = 0; i < n; i++)
    {
        FRe[i * step] /= factor;
        FIm[i * step] /= factor;
    }
}

// 2D Fast Fourier transform that calls the 1D FFT for each row and each column. fRe and fIm are the input and FRe and Fim are the output with the transformation
void fourier::FFT2D(int w, int h, const double *fRe, const double *fIm, double *FRe, double *FIm, bool inverse)
{
    //temporary buffers
    std::vector<double> Gr2(h * w * 3);
    std::vector<double> Gi2(h * w * 3);

    for(int y = 0; y < h; y++) // row
        for(int c = 0; c < 3; c++) // color channel
        {
            fourier::FFT(w, inverse, &fRe[y * w * 3 + c], &fIm[y * w * 3 + c], &Gr2[y * w * 3 + c], &Gi2[y * w * 3 + c], 3, 1);
        }
    for(int x = 0; x < w; x++) // column
        for(int c = 0; c < 3; c++) // color channel
        {
            fourier::FFT(h, inverse, &Gr2[x * 3 + c], &Gi2[x * 3 + c], &FRe[x * 3 + c], &FIm[x * 3 + c], w * 3, w);
        }
}


// Calculates the amplitude of *fRe and *fIm and puts the result in *fAmp
void fourier::calculateAmp(int n, int m, double *fAmp, const double *fRe, const double *fIm)
{
    for(int y = 0; y < m; y++)
        for(int x = 0; x < n; x++)
            for(int c = 0; c < 3; c++)
            {
                fAmp[n * 3 * y + 3 * x + c] = sqrt(fRe[n * 3 * y + 3 * x + c] * fRe[n * 3 * y + 3 * x + c] + fIm[n * 3 * y + 3 * x + c] * fIm[n * 3 * y + 3 * x + c]);
            }
}

// f is the image to be drawn
cv::Mat fourier::draw(int n, int m, const double *f, bool shift)
{
    cv::Mat fourier(n, m, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int y1 = 0; y1 < m; y1++)
        for(int x1 = 0; x1 < n; x1++)
        {
            int x = x1, y = y1;
            if(shift) { // Shift corners to center for the visualisation of fourier transform
                x = (x1 + n / 2) % n; y = (y1 + m / 2) % m;
            }
            cv::Vec3b color = fourier.at<cv::Vec3b>(cv::Point(x1,y1));

            for(int i = 0; i < 3; i++) {
                // calculate color values out of the array
                color[i] = int(f[3 * n * y + 3 * x + i]);

                // negative colors set to 0
                if (int(f[3 * n * y + 3 * x + i]) < 0) color[i] = 0;

                // set color components higher than 255 to 255
                if (int(f[3 * n * y + 3 * x + i]) > 255) color[i] = 255;

            }
            fourier.at<cv::Vec3b>(cv::Point(x1,y1))=color;
        }
    return fourier;
}