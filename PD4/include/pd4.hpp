#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
void Canny_Detection(cv::Mat bw_img, cv::Mat source_img, cv::Mat dst, int low_threshold);
void Sobel_Detection(cv::Mat bw_img, cv::Mat source_img);
void Laplacian_Detection(cv::Mat bw_img, cv::Mat source_img);
