#include "helper.hpp"



using namespace std;
const int H=128,W=128,c=3;
double fRe[H][W][3], fIm[H][W][3], fAmp[H][W][3]; //the signal's real part, imaginary part, and amplitude
double FRe[H][W][3], FIm[H][W][3], FAmp[H][W][3]; //the FT's real part, imaginary part and amplitude
double fRe2[H][W][3], fIm2[H][W][3], fAmp2[H][W][3]; //will become the signal again after IDFT of the spectrum
double FRe2[H][W][3], FIm2[H][W][3], FAmp2[H][W][3]; //filtered spectrum

int main()
{

    string image_path = "test.png";

    cv::Mat clarisse = load_image(image_path);


    //display_im(clarisse);

    vector<vector<vector<double>>> vect = cv_to_vector (clarisse);

    // int H=vect.size(),W=vect[1].size(),c=vect[1][1].size();

    //vector<vector<vector<double>>> fRe (H,vector<vector<double>>(W,vector<double>(c)));




    for(int j=0;j<H;j++) {
        for (int k = 0; k < W; k++) {
            for (int i = 0; i < c; i++) {
                fRe[j][k][i] = vect[j][k][i];
                //cout << fRe[j][k][i] << " ";
            }
            //cout << "     ";
        }
        //cout << endl;
    }




    FFT2D(W, H, false, fRe[0][0], fIm[0][0], FRe[0][0], FIm[0][0]);
    calculateAmp(W, H, FAmp[0][0], FRe[0][0], FIm[0][0]);
    draw(W, H, FRe[0][0]);
    // draw(W, H, FIm[0][0]);
    // draw(W, H, FAmp[0][0]);
    FFT2D(W, H, true, FRe[0][0], FIm[0][0], fRe2[0][0], fIm2[0][0]);
    calculateAmp(W, H, fAmp2[0][0], fRe2[0][0], fIm2[0][0]);
    draw(W, H, fRe2[0][0]);
    //draw(W, H, fIm2[0][0]);
    //draw(W, H, fAmp2[0][0]);

}
