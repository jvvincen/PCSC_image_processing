#ifndef ImageClass_H
#define ImageClass_H
#include <iostream>
#include <vector>


class ImageClass
{
public:

ImageClass(int rows, int cols, std::vector<u_char> pixels); //default constructor
int get_ncol();
int get_nrows();

int get_intensity(int x, int y);

std::vector<u_char> get_pixels();

void histogram();

private:
  int rows;
  int cols;

  std::vector<u_char> pixels;
};


#endif
