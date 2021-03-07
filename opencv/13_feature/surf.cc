#include <opencv2/opencv.hpp>

#include <opencv2/xfeatures2d.hpp>

#include <iostream>
#include <string>
#include <fstream>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

bool file_exists(const string& name) {
    ifstream f(name.c_str());
    return f.good();
}

int main(int argc, char* argv[]) {
    string basePath = "../../pics/";
    string img01_path, img02_path;
    if(argc > 2) {
        img01_path = argv[1];
        img02_path = argv[2];
    } else {
        img01_path = "01_left.jpg";
        img02_path = "01_right.jpg";
    }
    img01_path = basePath + img01_path;
    img02_path = basePath + img02_path;
    if(!file_exists(img01_path) || !file_exists(img02_path)) {
        cout << "file dosen't exits" << endl;
    }
    Mat image01 = imread(img01_path, IMREAD_COLOR); // left 
    Mat image02 = imread(img02_path, IMREAD_COLOR); // right 

    //灰度图转换  
    Mat gray01, gray02;
    cvtColor(image01, gray01, COLOR_RGB2GRAY);
    cvtColor(image02, gray02, COLOR_RGB2GRAY);

    //提取特征点   
    int minHessian = 400;
    Ptr<SURF> surfDetector = SURF::create(minHessian);   // 海塞矩阵阈值，在这里调整精度，值越大点越少，越精准 
    vector<KeyPoint> keyPoint1, keyPoint2;
    Mat descriptors1, descriptors2;
    surfDetector->detectAndCompute( gray01, noArray(), keyPoint1, descriptors1 );
    surfDetector->detectAndCompute( gray02, noArray(), keyPoint2, descriptors2 );

    //获得匹配特征点，并提取最优配对     
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<DMatch> > knn_matches;
    matcher->knnMatch( descriptors1, descriptors2, knn_matches, 2 );
    //-- Filter matches using the Lowe's ratio test
    const float ratio_thresh = 0.7f;
    std::vector<DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++) {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance) {
            good_matches.push_back(knn_matches[i][0]);
        }
    }

    Mat img_match;
    drawMatches(image01, keyPoint1, image02, keyPoint2, good_matches, img_match);
    imwrite("match.jpg", img_match);

}

 

// docker run -itd --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -p 9000:22 -p 9001:9001 -v /home/ysy/littleMickle:/home/littleMickle victorhcm/opencv:3.2.0-python3.4 /bin/bash