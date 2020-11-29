#include "helper.hpp"

cv::Mat load_image(std::string image_path)
{
  Mat image = imread(image_path, IMREAD_COLOR);
  if(image.empty())
  {
      std::cout << "Could not read the image: " << image_path << std::endl;
  }
  return image;
}

void display_im(cv::Mat image)
{
  imshow("Display window", image);
  int k = waitKey(0); // Wait for a keystroke in the windowimshow("Display window", clarisse);
  /*
  if(k == 's')
  {
      imwrite("cla.png", clarisse);
  }
  */
}

std::vector<uchar> cv_to_vector(Mat image)
{
  //assume single channel 2D matrix.
  std::vector<uchar> array;

  if (image.isContinuous()) {
    //array.assign(image.datastart, image.dataend); // <- has problems for sub-imagerix like image = big_image.row(i)
    std::cout << "coucou1" << '\n';
    array.assign(image.data, image.data + image.total()*image.channels());
  } else {
      std::cout << "COUCOU" << '\n';
    for (int i = 0; i < image.rows; ++i) {
      array.insert(array.end(), image.ptr<uchar>(i), image.ptr<uchar>(i)+image.cols*image.channels());
    }
  }

  return array;
}

std::vector<Mat> split_channels(Mat image)
{
  Mat ch1, ch2, ch3;
  // "channels" is a vector of 3 Mat arrays:
  std::vector<Mat> channels(3);
  // split img:
  split(image, channels);
  // get the channels (dont forget they follow BGR order in OpenCV)

  ch1 = channels[0];
  ch2 = channels[1];
  ch3 = channels[2];


  return channels;

}

std::vector<std::vector<uchar>> channels_to_vectors(Mat image)
{

  std::vector<Mat> channels = split_channels(image);
  std::vector<uchar> ch1_v = cv_to_vector(channels[0]);
  std::vector<uchar> ch2_v = cv_to_vector(channels[1]);
  std::vector<uchar> ch3_v = cv_to_vector(channels[2]);

  std::vector<std::vector<uchar>> im_vec {ch1_v, ch2_v, ch3_v};

  return im_vec;

}
