/*
canny边缘检测
思路：将原始图像转化为灰度图，用blur函数进行图像模糊以降噪，然后用canny函数进行边缘检测。
*/

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int main() {
	Mat SrcPic = imread("../../pics/01.jpg");
	Mat DstPic, edge, grayImage;

	//创建与src同类型和同大小的矩阵
	DstPic.create(SrcPic.size(), SrcPic.type());
	
	//将原始图转化为灰度图
	cvtColor(SrcPic, grayImage, COLOR_BGR2GRAY);

	//先使用3*3内核来降噪
	blur(grayImage, edge, Size(3, 3));

	//运行canny算子
	Canny(edge, edge, 3, 9, 3);

    imwrite("canny.jpg", edge);

	return 0;
}