#include "imageFourierClass.h"
using namespace cv;

int main(int argc, char **argv) {

    string image_path = "256.png";
    //string image_path = "photo2.png"; // not square

    cv::Mat image = load_square_image(image_path);
    cv::Mat sinus = imageFourierClass::create_sin_image(128);

    imageFourierClass::display_fourier(sinus, "sinus");
    imageFourierClass::display_fourier(image, image_path);
    destroyAllWindows();

    imageFourierClass::choose_filter(image);


    return 0;
}