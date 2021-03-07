#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("../../pics/01.jpg");

	Mat gray, dst, abs_dst;
	//高斯滤波消除噪声
	GaussianBlur(img, img, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//转换为灰度图
	cvtColor(img, gray, COLOR_RGB2GRAY);
	//使用Laplace函数
	//第三个参数：目标图像深度；第四个参数：滤波器孔径尺寸；第五个参数：比例因子；第六个参数：表示结果存入目标图
	Laplacian(gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	//计算绝对值，并将结果转为8位
	convertScaleAbs(dst, abs_dst);
    imwrite("laplace.jpg", abs_dst);
}