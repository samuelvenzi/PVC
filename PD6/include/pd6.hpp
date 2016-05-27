#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "stdio.h"

cv::Mat DetectCorners(cv::Mat image, double threshold);
cv::Mat GoodFeatures(cv::Mat image);
cv::Mat getCornerMap(cv::Mat cornerStrength, cv::Mat localMax, double threshold);
cv::Mat getCorners(cv::Mat cornerMap, cv::Mat image);

