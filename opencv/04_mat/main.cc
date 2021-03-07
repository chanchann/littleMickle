/*
RGB图像的通道顺序为BGR
现在主流的设备都适用无符号8位整数来（CV_8U）来表示像素亮度
一般像素址越大表示这个点越亮
灰度图用2维矩阵，彩色（多通道）图像用3维矩阵（M×N×3）表示

class CV_EXPORTS Mat
{
public:
 //一系列函数
 ...
 flag 参数中包含许多关于矩阵的信息，如：
 -Mat 的标识
 -数据是否连续
 -深度
 -通道数目

 int flags;
 //矩阵的维数，取值应该大于或等于 2
 int dims;
 //矩阵的行数和列数，如果矩阵超过 2 维，这两个变量的值都为-1
 int rows, cols;
 //指向数据的指针
 uchar* data;
 //指向引用计数的指针
 //如果数据是由用户分配的，则为 NULL
 int* refcount;
 //其他成员变量和成员函数
 ...
};



*/

#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;

// 构造方法
void test01() {
    // 3*2 图像元素是 8 位无符号整数类型，且有三个通道。图像的所有像素值被初始化为(0, 0, 255)。
    // 由于 OpenCV 中默认的颜色顺序为 BGR，因此这是一个全红色的图像
    //  [  0,   0, 255,   0,   0, 255;
    //     0,   0, 255,   0,   0, 255;
    //     0,   0, 255,   0,   0, 255]
    Mat M(3,2, CV_8UC3, Scalar(0,0,255));
    cout << "M = " << endl << " " << M << endl;
}

// create 
// 如果 create()函数指定的参数与图像之前的参数相同，则不进行实质的内存
// 申请操作；如果参数不同，则减少原始数据内存的索引，并重新申请内存。
// 使用 create()函数无法设置图像像素的初始值
void test02() {
    Mat M(2,2, CV_8UC3);//构造函数创建图像
    M.create(3,2, CV_8UC2);//释放内存重新创建图像
}

// Matlab 风格的创建对象方法
// 有些 type 参数如 CV_32F 未注明通道数目，这种情况下它表示单通道
void test03() {
    Mat Z = Mat::zeros(2,3, CV_8UC1);
    cout << "Z = " << endl << " " << Z << endl;
    Mat O = Mat::ones(2, 3, CV_32F);
    cout << "O = " << endl << " " << O << endl;
    Mat E = Mat::eye(2, 3, CV_64F);
    cout << "E = " << endl << " " << E << endl;
}
// 模板类 Vec，可以表示一个向量
// typedef Vec<uchar, 2> Vec2b;
// typedef Vec<uchar, 3> Vec3b;
// typedef Vec<uchar, 4> Vec4b;
// typedef Vec<short, 2> Vec2s;
// typedef Vec<short, 3> Vec3s;
// typedef Vec<short, 4> Vec4s;
// typedef Vec<int, 2> Vec2i;
// typedef Vec<int, 3> Vec3i;
// typedef Vec<int, 4> Vec4i;
// typedef Vec<float, 2> Vec2f;
// typedef Vec<float, 3> Vec3f;
// typedef Vec<float, 4> Vec4f;
// typedef Vec<float, 6> Vec6f;
// typedef Vec<double, 2> Vec2d;
// typedef Vec<double, 3> Vec3d;
// typedef Vec<double, 4> Vec4d;
// typedef Vec<double, 6> Vec6d;

// 8U 类型的 RGB 彩色图像可以使用 Vec3b，3 通道 float 类型的矩阵可以使用 Vec3f。
void test04() {
    Vec3b color; //用 color 变量描述一种 RGB 颜色
    color[0]=255; //B 分量
    color[1]=0; //G 分量
    color[2]=0; //R 分量
    cout << color << endl;
}
int main( int argc, char** argv ) {
    // test01();
    // test02();
    // test03();
    test04();
    waitKey(0);
    return 0;
}