/*
滤波处理分为两大类：线性滤波和非线性滤波。

线性滤波：方框滤波、均值滤波、高斯滤波

*/

#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("../../pics/01.jpg");
	Mat out;
	boxFilter(img, out, -1, Size(5, 5)); //-1指原图深度
    imwrite("boxFilter.jpg", out);
}
