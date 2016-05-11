#include "groudtruth.hpp"

double gtcompare(cv::Mat gt_img, cv::Mat out_img){
    double counter_hit = 0, counter_miss = 0, method_precision;
    
    for (int i = 0; i < out_img.rows; ++i)
    {
        for (int j = 0; j < out_img.cols; ++j)
        {
            if (gt_img.at<uchar>(i,j) == out_img.at<uchar>(i,j))
            {
                counter_hit++;
            }
            else{
                counter_miss++;
            }
        }
    }
    method_precision = counter_hit/(counter_miss + counter_hit);

    return method_precision;
}