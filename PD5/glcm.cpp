#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cv.h>

void glcm(cv::Mat src_img){
    cv::Mat glcmatrix(256,256, CV_32FC1);
    float HorMatrix[256][256];
    float FVMatrix[256][256];
    int total = 0;

    std::cout<<"2"<<std::endl;

    for (int i = 0; i < 256; ++i)
        for (int j = 0; j < 256; ++j)
            HorMatrix[i][j] = 0;

    std::cout<<"3"<<std::endl;
    for (int i = 0; i < src_img.rows; ++i)
    {
        for (int j = 0; j < src_img.cols-1; ++j)
        {   
                HorMatrix[(int)src_img.at<uchar>(i,j)][(int)src_img.at<uchar>(i,j+1)] += 1;
                total++;
        }
    }

    std::cout<<"4"<<std::endl;
    std::cout<<total<<std::endl;

    for (int i = 0; i < 256; ++i)
        for (int j = 0; j < 256; ++j)
            glcmatrix.at<float>(i,j) = (float)HorMatrix[i][j]/total;

    std::cout<<"5"<<std::endl;
    cv::FileStorage fs("GLCM.xml", cv::FileStorage::WRITE);
    fs << "GLCM" << glcmatrix;

    total = 0;
    for (int i = 1; i < src_img.rows; ++i)
    {
        for (int j = 0; j < src_img.cols-1; ++j)
        {
            FVMatrix[(int)src_img.at<uchar>(i,j)][(int)src_img.at<uchar>(i-1,j+1)] += 1;
            total++;
        }
    }
    std::cout<<total<<std::endl;
    for (int i = 0; i < 256; ++i)
        for (int j = 0; j < 256; ++j)
            glcmatrix.at<float>(i,j) = (float)FVMatrix[i][j]/total;

    cv::FileStorage fs2("GLCM45.xml", cv::FileStorage::WRITE);
    fs2 << "GLCM45" << glcmatrix;
}

int main(int argc, char const *argv[])
{
    cv::Mat src_img;
    std::cout<<"1"<<std::endl;
    src_img = cv::imread(argv[1]);
    cv::cvtColor(src_img, src_img, CV_BGR2GRAY);
    glcm(src_img);
    return 0;
}

