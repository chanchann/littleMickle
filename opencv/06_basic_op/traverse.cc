#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

//访问每个像素,指针的方式比较快
int main() {
	Mat img = imread("../../pics/01.jpg");
	for (int i = 0; i < img.rows; i++) {
		uchar* data = img.ptr<uchar>(i);  //获取第i行地址
		for (int j = 0; j < img.cols; j++) {
			 printf("%d\n",data[j]);
		}
	}
    return 0;
}