#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
	Mat SrcPic = imread("../../pics/01.jpg");
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //getStructuringElement函数返回的是指定形状和尺寸的结构元素
	Mat DstPic;
	erode(SrcPic, DstPic, element); //腐蚀操作
    imwrite("erode.jpg", DstPic);
	return 0;
}
