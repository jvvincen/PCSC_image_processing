#include "image.h"

int main(int argc, char **argv) {

    string image_path = "256.png";
    //string image_path = "photo2.png"; // not square

    cv::Mat image = helper::load_square_image(image_path);
    cv::Mat sinus = image::create_sin_image(128);

    image::display_fourier(sinus,"sinus");
    image::display_fourier(image,image_path);
    image::choose_filter(image);

    return 0;
}