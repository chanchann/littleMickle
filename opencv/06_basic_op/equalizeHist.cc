#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

//直方图均衡化
// 显然均衡化后的图片对比度变高了，变得更加明亮！

int main() {
	Mat img = imread("../../pics/01.jpg");
	Mat dst;
	cvtColor(img, img, COLOR_RGB2GRAY);
    imwrite("hist_gray.jpg", img);
	equalizeHist(img, dst);
    imwrite("hist.jpg", dst);
}