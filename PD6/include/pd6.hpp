#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

void DetectCorners(const cv::Mat& image);
cv::Mat getCornerMap(double qualityLevel);
void getCorners(std::vector<cv::Point> &points, const cv::Mat& cornerMap);
void drawOnImage(cv::Mat &image, const std::vector<cv::Point> &points,
                cv::Scalar color = cv::Scalar(255,255,255),
                int radius = 3, int thickness = 2);

