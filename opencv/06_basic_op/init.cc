#include<opencv2/opencv.hpp>   
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    //这些方式都是自己拥有独立的内存空间
	Mat img1(2, 2, CV_8UC3, Scalar(0, 0, 255));
	cout << img1 << endl;

	Mat img2;
    // random 数值
	img2.create(4, 4, CV_8UC3);
	cout << img2 << endl;

	Mat img3 = Mat::zeros(4, 4, CV_8UC3);
	cout << img3 << endl;

	Mat img4 = img3.clone();
	cout << img4 << endl;
    // different
    cout << "img3 address = " << &img3 << " img4 address = " << &img4 << endl;

	Mat img5;
	img3.copyTo(img5);
	cout << img5 << endl;
    cout << "img3 address = " << &img3 << " img5 address = " << &img5 << endl;

	//下面都是浅拷贝，指针指向同一个实例
	Mat img6 = img3;
    // img6 += 1;
	Mat img7(img3);
    cout << "img3 " << img3 << endl;
    cout << "img6 " << img6 << endl;
    // 不能通过这个地址判断是否是浅拷贝，因为他内部有个data*指向的而不是外部
    cout << "img6 address = " << &img6 << " img7 address = " << &img7 << endl;

	waitKey(0);
	return 0;
}