//
// Created by leonard on 26.12.20.
//

#include "image.h"

// Display 3 images in a single window (real part, imaginary part, amplitude)
void display_real_im_amp(cv::Mat real, cv::Mat im, cv::Mat amp, string title) {
    cv::Mat matDst(cv::Size(real.cols * 3, real.rows), real.type(), cv::Scalar::all(0));
    cv::Mat matRoi = matDst(cv::Rect(0, 0, real.cols, real.rows));
    real.copyTo(matRoi);
    matRoi = matDst(cv::Rect(real.cols, 0, real.cols, real.rows));
    im.copyTo(matRoi);
    matRoi = matDst(cv::Rect(real.cols * 2, 0, real.cols, real.rows));
    amp.copyTo(matRoi);
    fourier::display_im(matDst, title);
    matDst.release();
    matRoi.release();
}

void image::display_fourier(cv::Mat image, string title) {
    int H = image.rows, W = image.cols, c = 3;
    // pointers that will be needed for the fft
    double *fRe = new double[H * W * c], *fIm = new double[H * W * c], *fAmp = new double[H * W * c];
    double *FRe = new double[H * W * c], *FIm = new double[H * W * c], *FAmp = new double[H * W * c];
    double *fRe2 = new double[H * W * c], *fIm2 = new double[H * W * c], *fAmp2 = new double[H * W * c];

    fRe = helper::cv_to_pointer(image);

    // Draw the image without transformation
    fourier::calculateAmp(W, H, fAmp, fRe, fIm);
    cv::Mat untransformed_real = fourier::draw(W, H, fRe, false);
    cv::Mat untransformed_im = fourier::draw(W, H, fIm, false);
    cv::Mat untransformed_amp = fourier::draw(W, H, fAmp, false);
    display_real_im_amp(untransformed_real, untransformed_im, untransformed_amp,
                        title + " - Untransformed - (Real, Imaginary, Amplitude)");

    // Calculate and draw FFT
    fourier::FFT2D(W, H, fRe, fIm, FRe, FIm);
    delete[] fRe;
    delete[] fIm;
    delete[] fAmp;
    fourier::calculateAmp(W, H, FAmp, FRe, FIm);
    cv::Mat transformed_real = fourier::draw(W, H, FRe, true);
    cv::Mat transformed_im = fourier::draw(W, H, FIm, true);
    cv::Mat transformed_amp = fourier::draw(W, H, FAmp, true);
    display_real_im_amp(transformed_real, transformed_im, transformed_amp,
                        title + " - Transformed - (Real, Imaginary, Amplitude)");

    // Calculate and draw the inverse of FFT to get the image back
    fourier::FFT2D(W, H, FRe, FIm, fRe2, fIm2, true);
    fourier::calculateAmp(W, H, fAmp2, fRe2, fIm2);
    cv::Mat retransformed_real = fourier::draw(W, H, fRe2, false);
    cv::Mat retransformed_im = fourier::draw(W, H, fIm2, false);
    cv::Mat retransformed_amp = fourier::draw(W, H, fAmp2, false);
    display_real_im_amp(retransformed_real, retransformed_im, retransformed_amp,
                        title + " - Re-transformed - (Real, Imaginary, Amplitude)");
    delete[] fRe2; // clear memory
    delete[] fIm2;
    delete[] fAmp2;
    delete[] FRe;
    delete[] FIm;
    delete[] FAmp;

    int k = cv::waitKey(0);

}

// Calculate and draw inverse fft with pass applied
void image::display_blur(cv::Mat image, double radius1, int pass, double radius2) {
    int H = image.rows, W = image.cols, c = 3;
    double *fRe = new double[H * W * c], *fIm = new double[H * W * c], *FRe = new double[H * W * c], *FIm = new double[
    H * W * c];
    double *FReBlur = new double[H * W * c], *FImBlur = new double[H * W * c], *fReBlur = new double[H * W *
                                                                                                     c], *fImBlur = new double[
    H * W * c];
    fRe = helper::cv_to_pointer(image);
    fourier::FFT2D(W, H, fRe, fIm, FRe, FIm);
    delete[] fRe;
    delete[] fIm;
    FReBlur = filter::blur(FRe, radius1, H, W, pass, radius2);
    delete[] FRe;
    FImBlur = filter::blur(FIm, radius1, H, W, pass, radius2);
    delete[] FIm;
    fourier::FFT2D(W, H, FReBlur, FImBlur, fReBlur, fImBlur, true);
    delete[] fImBlur;
    cv::Mat blur_transformed_re = fourier::draw(W, H, FReBlur, true);
    delete[] FReBlur;
    cv::Mat blur_transformed_im = fourier::draw(W, H, FImBlur, true);
    delete[] FImBlur;
    cv::Mat blur_retransformed_re = fourier::draw(W, H, fReBlur, false);
    delete[] fReBlur;
    string title = "Blurred with a radius divided by ";
    title.append(to_string(radius1)).append(" - (Real, Imaginary, Re-transformed)");
    display_real_im_amp(blur_transformed_re, blur_transformed_im, blur_retransformed_re, title);
    blur_transformed_re.release();
    blur_transformed_im.release();
    blur_retransformed_re.release();
    image.release();
    //cv::imwrite("0.png",blur_retransformed_re);
}

// interaction with the user to choose the filter
void image::choose_filter(cv::Mat image) {
    int filter;
    double radius_ratio;
    double radius_ratio2;

    while (filter < 0 || filter > 4) {
        cout
                << "Add a filter (1 : low pass filter || 2 : high pass filter || 3 : select band pass || 4 : unselect band pass || 0 to finish) \n";
        cin >> filter;
        if (filter == 0) { return ; }
    }
    cout << "Radius relative to the size in % : \n";
    cin >> radius_ratio;
    double radius = 100.0 / radius_ratio;

    if (filter > 2) {
        cout << "2nd radius relative to the size in % : \n";
        cin >> radius_ratio2;
        double radius2 = 100.0 / radius_ratio2;
        image::display_blur(image, radius, filter, radius2);
    } else {
        image::display_blur(image, radius, filter);
    }
    int k1 = cv::waitKey(0);

}

// create a sinusoidal image to check if the fft works
cv::Mat image::create_sin_image(int size) {
    int n = size, m = n;
    cv::Mat sinus(n, m, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int y1 = 0; y1 < m; y1++)
        for (int x1 = 0; x1 < m; x1++) {
            cv::Vec3b color = sinus.at<cv::Vec3b>(cv::Point(x1, y1));
            color[2] = 126 + 63 * sin(M_PI * y1 / 16.0) + 63 * sin(M_PI * x1 / 16.0);
            color[1] = 126 + 63 * sin(M_PI * y1 / 16.0) + 63 * sin(M_PI * x1 / 16.0);

            sinus.at<cv::Vec3b>(cv::Point(x1, y1)) = color;
        }
    return sinus;
}