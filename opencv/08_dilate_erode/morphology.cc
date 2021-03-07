/*
开运算：先腐蚀再膨胀，用来消除小物体

闭运算：先膨胀再腐蚀，用于排除小型黑洞

形态学梯度：就是膨胀图与俯视图之差，用于保留物体的边缘轮廓。

顶帽：原图像与开运算图之差，用于分离比邻近点亮一些的斑块。

黑帽：闭运算与原图像之差，用于分离比邻近点暗一些的斑块。

opencv里有一个很好的函数getStructuringElement，我们只要往这个函数传相应的处理参数，就可以进行相应的操作了，使用起来非常方便。
*/
#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

//高级形态学处理
int main()
{
	Mat img = imread("../../pics/01.jpg");
	Mat gradient, tophat;
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
		
	//高级形态学处理，调用这个函数就可以了，具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学梯度处理
    // MorphTypes https://docs.opencv.org/master/d4/d86/group__imgproc__filter.html#ga7be549266bad7b2e6a04db49827f9f32
	morphologyEx(img, gradient, MORPH_GRADIENT, element);
    morphologyEx(img, tophat, MORPH_TOPHAT , element);
    imwrite("gradient.jpg", gradient);
    imwrite("tophat.jpg", tophat);
}
