#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

//双边滤波
int main() {
	Mat img = imread("../../pics/01.jpg");
	Mat out;
	bilateralFilter(img, out, 25, 25 * 2, 25 / 2);
	imwrite("bilateralFilter.jpg", out);

}