/*
图像二值化操作
两种方法，全局固定阈值二值化和局部自适应阈值二值化
全局固定阈值很容易理解，就是对整幅图像都是用一个统一的阈值来进行二值化；
局部自适应阈值则是根据像素的邻域块的像素值分布来确定该像素位置上的二值化阈值
*/

#include <opencv2/opencv.hpp>   
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat image = imread("../../pics/01.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);  //注意了，必须是载入灰度图
	if (image.empty()) {
		cout << "read image failure" << endl;
		return -1;
	}

	// 全局二值化
	int th = 100;
	Mat global;
    // https://docs.opencv.org/3.4/d7/d1b/group__imgproc__misc.html#gae8a4a146d1ca78c626a53577199e9c57
	threshold(image, global, th, 255, THRESH_BINARY_INV);

	// 局部二值化
	int blockSize = 25;
	int constValue = 10;
	Mat local;
	adaptiveThreshold(image, local, 255, ADAPTIVE_THRESH_MEAN_C , THRESH_BINARY_INV, blockSize, constValue);

    imwrite("global.jpg", global);
    imwrite("local.jpg", global);

	return 0;
}