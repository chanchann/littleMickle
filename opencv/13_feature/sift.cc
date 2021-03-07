#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>


#include <iostream>
#include <string>
#include <fstream>

using namespace cv;
using namespace std;

bool file_exists(const string& name) {
    ifstream f(name.c_str());
    return f.good();
}

int main(int argc, char* argv[]) {
    string basePath = "../../pics/";
    string img01_path, img02_path;
    if(argc > 2) {
        img01_path = argv[1];
        img02_path = argv[2];
    } else {
        img01_path = "01_left.jpg";
        img02_path = "01_right.jpg";
    }
    img01_path = basePath + img01_path;
    img02_path = basePath + img02_path;
    if(!file_exists(img01_path) || !file_exists(img02_path)) {
        cout << "file dosen't exits" << endl;
    }
    Mat image01 = imread(img01_path, IMREAD_COLOR); // left 
    Mat image02 = imread(img02_path, IMREAD_COLOR); // right 

    //灰度图转换  
    Mat gray01, gray02;
    cvtColor(image01, gray01, COLOR_RGB2GRAY);
    cvtColor(image02, gray02, COLOR_RGB2GRAY);

    //提取特征点   
    int numFeatures = 20;
    Ptr<SIFT> dectector = SIFT::create(numFeatures);
    vector<KeyPoint> keyPoint1, keyPoint2;
    surfDetector->detect(gray01, keyPoint1);
    surfDetector->detect(gray02, keyPoint2);

    //特征点描述，为下边的特征点匹配做准备    

}