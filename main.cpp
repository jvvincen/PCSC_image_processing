#include "helper.hpp"

using namespace std;


int main()
{
  std::string image_path = "../../cla.jpg";

cv::Mat clarisse = load_image(image_path);

//  display_im(clarisse);
  std::vector<std::vector<uchar>> vectorC = channels_to_vectors (clarisse);
  std::cout << vectorC[0][10] << std::endl;

}
