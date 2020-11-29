#include "helper.hpp"


using namespace std;


int main()
{

    string image_path = "../../cla.jpg";

    cv::Mat clarisse = load_image(image_path);

    //display_im(clarisse);
    vector<vector<vector<int>>> vect = cv_to_vector (clarisse);
    for (int i=0;i<vect.size();i++){
        for(int j=0;j<vect[i].size();j++){
            for(int k=0;k<vect[i][j].size();k++){
                cout << vect[i][j][k] << " ";
            }
            cout << endl;
        }

    }


}

