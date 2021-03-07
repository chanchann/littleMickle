/*
使用cv :: cvtColor将图像从BGR转换为灰度格式
将转换的图像保存在磁盘上的文件（使用cv :: imwrite）
*/
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;
int main( int argc, char** argv ) {
    string imageName( "../../pics/01.jpg" ); // by default
    Mat image;
    image = imread( imageName, IMREAD_COLOR );
    if(!image.data ) {
        printf( " No image data \n " );
        return -1;
    }
    Mat gray_image;
    imwrite("./color.jpg", image);
    cvtColor( image, gray_image, COLOR_BGR2GRAY );
    imwrite( "./gray.jpg", gray_image );
    // namedWindow( imageName, WINDOW_AUTOSIZE );
    // namedWindow( "Gray image", WINDOW_AUTOSIZE );
    // imshow( imageName, image );
    // imshow( "Gray image", gray_image );
    waitKey(0);
    return 0;
}