/*
第二种是比率
*/
#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

//图片的缩小与放大
int main() {
    Mat img = imread("../../pics/01.jpg");
    Mat dst;
    resize(img, dst, Size(), 0.5, 0.5); // 长宽都变为原来的0.5倍
    imwrite("resize_ratio.jpg", dst);
}