/*
resize函数可以将源图像精确地转化为指定尺寸的目标图像。
要缩小图像，一般推荐使用CV_INETR_AREA来插值；若要放大图像，推荐使用CV_INTER_LINEAR。

现在说说调用方式

第一种，规定好你要图片的尺寸，就是你填入你要的图片的长和高
*/

#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

//图片的缩小与放大
int main() {
    Mat img = imread("../../pics/01.jpg");
    Mat dst = Mat::zeros(512, 512, CV_8UC3); //我要转化为512*512大小的
    resize(img, dst, dst.size());

    imwrite("resize.jpg", dst);
}