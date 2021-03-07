/*
腐蚀和膨胀是最基本的形态学运算。

腐蚀和膨胀是针对白色部分（高亮部分）而言的。

膨胀就是对图像高亮部分进行“领域扩张”，效果图拥有比原图更大的高亮区域；腐蚀是原图中的高亮区域被蚕食，效果图拥有比原图更小的高亮区域。

膨胀

膨胀就是求局部最大值的操作，从图像直观看来，就是将图像光亮部分放大，黑暗部分缩小。
*/

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
	dilate(img, out, element);
    imwrite("dilate.jpg", out);
}