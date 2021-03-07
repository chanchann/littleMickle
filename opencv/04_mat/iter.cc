/*
Mat 也增加了迭代器的支持，以便于矩阵元素的遍历。

*/

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    Mat grayim(600, 800, CV_8UC1);
    Mat colorim(600, 800, CV_8UC3);
    //遍历所有像素，并设置像素值
    MatIterator_<uchar> grayit, grayend;
    for(auto it = grayim.begin<uchar>(); it != grayim.end<uchar>(); it++) {
        *it = rand() & 255;
    }
    //遍历所有像素，并设置像素值
    for(auto it = colorim.begin<Vec3b>(); it != colorim.end<Vec3b>(); it++) {
        (*it)[0] = rand()%255; //Blue
        (*it)[1] = rand()%255; //Green
        (*it)[2] = rand()%255; //Red
    }
    imwrite("./gray.jpg", grayim);
    imwrite("./color.jpg", colorim);
    waitKey(0);
    return 0;
}
