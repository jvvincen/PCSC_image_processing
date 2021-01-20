//
// Created by leonard on 26.12.20.
//

#include "helper.h"

cv::Mat helper::load_image(std::string image_path)
{
    cv::Mat image = imread(image_path, cv::IMREAD_COLOR);
    if(image.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
    }
    return image;
}
// Set the rest of the color to 0 to have a power of 2 squared image if it isn't the case. Only way for the fft algorithm to work
cv::Mat helper::load_square_image(std::string image_path) {
    /*!
     *
     */
    cv::Mat image = helper::load_image(image_path);

    int H = image.rows, W = image.cols;
    int square_size = max(H, W);
    int log_2 = ceil(log2(square_size));
    square_size = pow(2, log_2);
    cv::Mat sqrt_im(square_size, square_size, CV_8UC3, cv::Scalar(0, 0, 0));
    for (int y = 0; y < H; y++)
          for (int x = 0; x < W; x++) {
              cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x, y));
              sqrt_im.at<cv::Vec3b>(cv::Point(x, y)) = color;
        }
    for (int y = H; y < square_size; y++)
        for (int x = W; x < square_size; x++) {
              cv::Vec3b color = sqrt_im.at<cv::Vec3b>(cv::Point(x, y));
              for (int i = 0; i < 3; i++) {
                  color[i] = 0;
              }
              sqrt_im.at<cv::Vec3b>(cv::Point(x, y)) = color;
          }
    return sqrt_im;
}

vector<vector<vector<double>>> helper::cv_to_vector(cv::Mat image)
{
    //assume single channel 2D matrix.

    int H=image.rows,W=image.cols,c=3;
    vector<vector<vector<double>>> row ;
    if (image.isContinuous()) {
        std::cout << "coucou1" << '\n';

        for(int j=0;j<H;j++){
            vector<vector<double>> column;
            for(int k=0;k<W;k++){
                vector<double> color;
                for (int i=0;i<c;i++){
                    auto val=static_cast<double>(image.at<cv::Vec3b>(j,k)[i]);
                    color.push_back(val);
                }
                column.push_back(color);
            }
            row.push_back(column);
        }
    } else {
        std::cout << "COUCOU" << '\n';

    }

    return row;
}

// single chanel 3D array
double * helper::cv_to_pointer(cv::Mat image) {
    double H = image.rows, W = image.cols, c = 3;
    double * ptr;
    ptr=(new double[(int)(H*W*c)]);

    for (int i=0;i<W*H*c;i++){
        int x,y,indexc;
        y=(int)floor((double)i/(W*c));
        x=(int)(floor((double)i/c))%(int)W;
        indexc=i%3;

        ptr[i]=static_cast<double>(image.at<cv::Vec3b>(cv::Point(x,y))[indexc]);
    }

    return ptr;
}