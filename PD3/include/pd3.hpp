#include "opencv2/opencv.hpp"
#include <iostream>
#include "cstdio"
#include "string"
#include "cmath"
#include "climits"

cv::Mat template_creator(cv::Mat img, int template_size, cv::Point pos);
int cmptemplate(cv::Mat templL, cv::Mat templR);