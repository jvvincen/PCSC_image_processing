#include "helper.hpp"
#include "ImageClass.hpp"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main()
{
  std::string image_path = "../cla.jpg";

  cv::Mat clarisse = load_image(image_path);
  cv::Mat clarisse_grise;
  cv::cvtColor(clarisse, clarisse_grise, cv::COLOR_BGR2GRAY);

  //display_im(clarisse);
  //std::vector<std::vector<uchar>> vec = channels_to_vectors(clarisse);
  //std::cout << vectorC[0][10] << std::endl;

  //display_im(vec_to_cv(vec,1280, 960));

  std::vector<uchar> clarisse_vec = cv_to_vector(clarisse_grise);

  int rows = clarisse_grise.rows;
  int cols = clarisse_grise.cols;

  ImageClass first_image(rows, cols, clarisse_vec);
//std::cout << first_image.get_intensity(100, 100) << '\n';
  //first_image.histogram();

  first_image.histogram();

  display_im(vec_to_cv(first_image.get_pixels(), first_image.get_nrows(),
                        first_image.get_ncol()));




  //IDJ image_de_juliette;


}
