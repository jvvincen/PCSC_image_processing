#include <iostream>
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


void ImageClass::histogram(int nb_bins)
{
  std::vector<int> bins(nb_bins, 0);
  for (int item : pixels) {
    //std::cout << item << " - ";
 }
}
