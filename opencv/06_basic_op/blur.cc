#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int main() {
	Mat SrcPic = imread("../../pics/01.jpg");
	if(SrcPic.empty()) {
        cout << "load pic failed" << endl;
        return -1;
    }
	Mat DstPic;
	blur(SrcPic, DstPic, Size(7, 7));
    imwrite("blur.jpg", DstPic);
	return 0;
}