/*
均值滤波就是方框滤波的一个特殊情况。
均值滤波的缺点就是不能很好地保护细节，在图像去燥的同时也破坏了图像的而细节部分，从而使图像变得模糊，不能很好的去除噪点。
*/

#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;
int main() {
	Mat img = imread("../../pics/01.jpg");
	Mat out;
	blur(img, out,Size(5, 5));//-1指原图深度
	imwrite("meanFilter.jpg", out);
}