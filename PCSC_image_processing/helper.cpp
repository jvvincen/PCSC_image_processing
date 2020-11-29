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
  int k = cv::waitKey(0); // Wait for a keystroke in the windowimshow("Display window", clarisse);
  /*
  if(k == 's')
  {
      imwrite("cla.png", clarisse);
  }
  */
}



vector<vector<vector<int>>> cv_to_vector(cv::Mat image)
{
    //assume single channel 2D matrix.


    int array[3][image.rows][image.cols];
    vector<vector<vector<int>>> color;
    if (image.isContinuous()) {
        std::cout << "coucou1" << '\n';

        for (int i=0;i<3;i++){
            vector<vector<int>> row;
            for(int j=0;j<image.rows;j++){
                vector<int> column;
                for(int k=0;k<image.cols;k++){
                    int val=static_cast<int>(image.at<cv::Vec3b>(j,k)[i]);
                    column.push_back(val);
                }
                row.push_back(column);
            }
            color.push_back(row);
        }
    } else {
        std::cout << "COUCOU" << '\n';

    }

    return color;

}

