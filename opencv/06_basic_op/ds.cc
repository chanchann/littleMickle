#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

//常见数据结构使用方法总结
int main() {
	//Mat的用法
	Mat m1(2, 2, CV_8UC3, Scalar(0, 0, 255)); //其中的宏的解释：CV_[位数][带符号与否][类型前缀]C[通道数]
	cout << m1 << endl;

	//或者
	Mat m2;
	m2.create(4, 5, CV_8UC(2));


	//点的表示:Point
	Point p;
	p.x = 1; //x坐标
	p.y = 1; //y坐标

	//或者
	Point p2(1, 1);

	//颜色的表示：Scalar(b,g,r);注意不是rgb，注意对应关系
	Scalar(1, 1, 1);

	//尺寸的表示:Size
	Size(5, 5);// 宽度和高度都是5

	//矩形的表示：Rect，成员变量有x,y,width,height
	Rect r1(0, 0, 100, 60);
	Rect r2(10, 10, 100, 60);
	Rect r3 = r1 | r2; //两个矩形求交集
	Rect r4 = r1 & r2; //两个矩形求并集


}