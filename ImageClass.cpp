#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "ImageClass.hpp"


ImageClass::ImageClass(int rows, int cols, std::vector<u_char> pixels)
  :rows(rows), cols(cols), pixels(pixels)
{

}

int ImageClass::get_ncol(){return cols;}
int ImageClass::get_nrows(){return rows;}

std::vector<u_char> ImageClass::get_pixels(){return pixels;}

int ImageClass::get_intensity(int x, int y)
{
  int index = cols*x + y;
  return pixels[index];
}


void ImageClass::histogram()
{

  std::vector<int> bins(255, 0);

  for (int item : pixels) {
    bins[item] += 1;
 }


  std::ofstream histogram("../histogram.txt");
  std::ostream_iterator<int> output_iterator(histogram, ",");
  std::copy(bins.begin(), bins.end(), output_iterator);

  histogram.close();


  system("python ../plot_histogram.py");
}
