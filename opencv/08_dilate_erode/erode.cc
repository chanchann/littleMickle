#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

//膨胀
int main() {
	Mat img = imread("../../pics/01.jpg");
	Mat out;
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
	//膨胀操作
	erode(img, out, element);
    imwrite("erode.jpg", out);
}