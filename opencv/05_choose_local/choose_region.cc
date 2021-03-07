/*
这些方法并不进行内存的复制操作。如果将局部区域赋值给新的 Mat 对
象，新对象与原始对象共用相同的数据区域，不新申请内存，
*/

#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

int main() {
    Mat A = Mat::eye(10, 10, CV_32S);
    cout << A << endl;
    
    Mat line1 = A.row(1);
    cout << line1 << endl;
    
    Mat col2 = A.col(2);
    cout << col2 << endl;
    
    A.row(2) = A.row(3) * 2;
    cout << A << endl;

    // 用 Range 选择多行或多列
    //提取第 1 到 3 列（不包括 3）
    Mat B = A(Range::all(), Range(1, 3));
    cout << B << endl;
    //提取 B 的第 5 至 9 行（不包括 9）
    //其实等价于 C = A(Range(5, 9), Range(1, 3))
    Mat C = B(Range(5, 9), Range::all());
    cout << C << endl;

    // 对角线元素
    Mat diag = A.diag();
    cout << diag << endl;
}