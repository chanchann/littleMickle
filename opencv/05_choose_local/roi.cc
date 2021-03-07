#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

int main() {
    //创建宽度为 320，高度为 240 的 3 通道图像
    Mat img(Size(320,240),CV_8UC3);
    //roi 是表示 img 中 Rect(10,10,100,100)区域的对象
    Mat roi1(img, Rect(10,10,100,100));
    Mat roi2 = img(Rect(10,10,100,100));
    Mat roi3 = img(Range(10,100),Range(10,100));
    Mat roi4(img, Range(10,100), Range(10,100));
}