#include "helper.hpp"



using namespace std;

cv::Mat load_image(std::string image_path)
{
  cv::Mat image = imread(image_path, cv::IMREAD_COLOR);
  if(image.empty())
  {
      std::cout << "Could not read the image: " << image_path << std::endl;
  }
  return image;
}

void display_im(cv::Mat image)
{
  imshow("Display window", image);
  int k = cv::waitKey(0);// Wait for a keystroke in the windowimshow("Display window", clarisse);
  /*
  if(k == 's')
  {
      imwrite("cla.png", clarisse);
  }
  */
}


vector<vector<vector<double>>> cv_to_vector(cv::Mat image)
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


void FFT(int n, bool inverse, const double *gRe, const double *gIm, double *GRe, double *GIm, int stride, double factor)
{
    //Calculate h=log_2(n)
    int h = 0;
    int p = 1;
    while(p < n)
    {
        p *= 2;
        h++;
    }
    //Bit reversal
    GRe[(n - 1) * stride] = gRe[(n - 1) * stride];
    GIm[(n - 1) * stride] = gIm[(n - 1) * stride];
    int j = 0;
    for(int i = 0; i < n - 1; i++)
    {
        GRe[i * stride] = gRe[j * stride];
        GIm[i * stride] = gIm[j * stride];
        int k = n / 2;
        while(k <= j)
        {
            j -= k;
            k /= 2;
        }
        j += k;
    }
    //Calculate the FFT
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
                double t1 = u1 * GRe[i1 * stride] - u2 * GIm[i1 * stride];
                double t2 = u1 * GIm[i1 * stride] + u2 * GRe[i1 * stride];
                GRe[i1 * stride] = GRe[i * stride] - t1;
                GIm[i1 * stride] = GIm[i * stride] - t2;
                GRe[i * stride] += t1;
                GIm[i * stride] += t2;
            }
            double z =  u1 * ca - u2 * sa;
            u2 = u1 * sa + u2 * ca;
            u1 = z;
        }
        sa = sqrt((1.0 - ca) / 2.0);
        if(!inverse) sa =- sa;
        ca = sqrt((1.0 + ca) / 2.0);
    }
    //Divide through the factor, e.g. n
    for(int i = 0; i < n; i++)
    {
        GRe[i * stride] /= factor;
        GIm[i * stride] /= factor;
    }
}


void FFT2D(int w, int h, bool inverse, const double *gRe, const double *gIm, double *GRe, double *GIm)
{
    //temporary buffers
    std::vector<double> Gr2(h * w * 3);
    std::vector<double> Gi2(h * w * 3);

    for(int y = 0; y < h; y++) // for each row
        for(int c = 0; c < 3; c++) // for each color channel
        {
            FFT(w, inverse, &gRe[y * w * 3 + c], &gIm[y * w * 3 + c], &Gr2[y * w * 3 + c], &Gi2[y * w * 3 + c], 3, 1);
        }
    for(int x = 0; x < w; x++) // for each column
        for(int c = 0; c < 3; c++) // for each color channel
        {
            FFT(h, inverse, &Gr2[x * 3 + c], &Gi2[x * 3 + c], &GRe[x * 3 + c], &GIm[x * 3 + c], w * 3, inverse ? w : h);
        }
}


//Calculates the amplitude of *gRe and *gIm and puts the result in *gAmp
void calculateAmp(int n, int m, double *gAmp, const double *gRe, const double *gIm)
{
    for(int y = 0; y < m; y++)
        for(int x = 0; x < n; x++)
            for(int c = 0; c < 3; c++)
            {
                gAmp[n * 3 * y + 3 * x + c] = sqrt(gRe[n * 3 * y + 3 * x + c] * gRe[n * 3 * y + 3 * x + c] + gIm[n * 3 * y + 3 * x + c] * gIm[n * 3 * y + 3 * x + c]);
            }
}

void draw(int n, int m, const double *g) //g is the image to be drawn
{
    cv::Mat fourier(n, m, CV_8UC3, cv::Scalar(0, 0, 0));
    for(int y = 0; y < m; y++)
        for(int x = 0; x < n; x++)
        {

            cv::Vec3b color = fourier.at<cv::Vec3b>(cv::Point(x,y));

            //calculate color values out of the floating point buffer
            color[0] = int(g[3 * n * y + 3 * x + 0]);
            color[1] = int(g[3 * n * y + 3 * x + 1]);
            color[2] = int(g[3 * n * y + 3 * x + 2]);
            //negative colors give confusing effects so set them to 0
            if(color[0] < 0) color[0] = 0;
            if(color[1] < 0) color[1] = 0;
            if(color[2] < 0) color[2] = 0;
            //set color components higher than 255 to 255
            if(color[0] > 255) color[0] = 255;
            if(color[1] > 255) color[1] = 255;
            if(color[2] > 255) color[2] = 255;
            fourier.at<cv::Vec3b>(cv::Point(x,y))=color;
        }
    display_im(fourier);
}