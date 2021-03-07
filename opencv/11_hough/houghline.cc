/*
我们如何在图像中快速识别出其中的圆和直线？一个非常有效的方法就是霍夫变换，它是图像中识别各种几何形状的基本算法之一。

霍夫线变换是一种在图像中寻找直线的方法。OpenCV中支持三种霍夫线变换，分别是标准霍夫线变换、多尺度霍夫线变换、累计概率霍夫线变换。

调用函数HoughLines来调用标准霍夫线变换和多尺度霍夫线变换。HoughLinesP函数用于调用累积概率霍夫线变换。
*/
#include<opencv2/opencv.hpp>   

using namespace std;
using namespace cv;

//边缘检测
int main() {
    Mat srcImage = imread("../../pics/01.jpg");
    Mat midImage, dstImage;
    //边缘检测
    Canny(srcImage, midImage, 50, 200, 3);
    //灰度化
    cvtColor(midImage, dstImage, cv::COLOR_GRAY2BGR);
    // 定义矢量结构存放检测出来的直线
    vector<Vec2f> lines;
    //通过这个函数，我们就可以得到检测出来的直线集合了
    HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
    //这里注意第五个参数，表示阈值，阈值越大，表明检测的越精准，速度越快，得到的直线越少（得到的直线都是很有把握的直线）
    //这里得到的lines是包含rho和theta的，而不包括直线上的点，所以下面需要根据得到的rho和theta来建立一条直线

    //依次画出每条线段
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0]; //就是圆的半径r
        float theta = lines[i][1]; //就是直线的角度
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000 * (a));

        line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA); //Scalar函数用于调节线段颜色，就是你想检测到的线段显示的是什么颜色
        imwrite("midImage.jpg", midImage);
        imwrite("dstImage.jpg", dstImage);
    }
    return 0;
}
