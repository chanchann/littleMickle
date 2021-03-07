/*
高斯滤波，可以消除高斯噪声，广泛应用于图像处理的减噪过程。

*/

#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("../../pics/01.jpg");
	Mat out;
	GaussianBlur(img, out, Size(3, 3), 0, 0);
	imwrite("GaussianBlur.jpg", out);
}