#include "pd6.hpp"

//compute Harris corners
cv::Mat DetectCorners(cv::Mat image, double threshold){
    cv::Mat cornerStrength;
    cv::Mat cornerMap;
    
    cv::cornerHarris(image, cornerStrength,
        3,  //neighborhood size
        3,  //aperture size
        0.01); //Harris parameter
    
    cv::Mat dilated;
    cv::Mat localMax;
    
    cv::dilate(cornerStrength, dilated, cv::Mat());
    cv::compare(cornerStrength, dilated, localMax, cv::CMP_EQ);
    cornerMap = getCornerMap(cornerStrength, localMax, threshold);

    image = getCorners(cornerMap, image);

    return image;
}

cv::Mat GoodFeatures(cv::Mat image){
    std::vector<cv::Point> corners;
   
    cv::goodFeaturesToTrack(image, corners,
                            500,    //maximum number of corners to be returned
                            0.01,   //quality level
                            10);    //minimum allowed distance between points

    std::vector<cv::Point>::const_iterator it = corners.begin();
    //for all corners
    while(it!=corners.end()){
        //draw a circle at each corner location
        cv::circle(image, *it, 3, cv::Scalar(255,255,255), 3);
        ++it;
    }

    return image;
}

//Get corner map from the computed Harris values
cv::Mat getCornerMap(cv::Mat cornerStrength, cv::Mat localMax, double threshold){
    cv::Mat cornerMap;
    cv::Mat cornerTh;
    
    cv::threshold(cornerStrength, cornerTh, threshold, 255, cv::THRESH_BINARY);

    //convert to 8-bit image
    cornerTh.convertTo(cornerMap,CV_8U);
    //non-maxima supression
    cv::bitwise_and(cornerMap,localMax,cornerMap);

    return cornerMap;
}

//Get the feature points from the computed corner map
cv::Mat getCorners(cv::Mat cornerMap, cv::Mat image){
    cv::Scalar color = cv::Scalar(255,255,255);
    int radius = 3;
    int thickness = 2;
    //iterate over the pixels to obtain all features
    std::vector<cv::Point> points;

    for (int i = 0; i < cornerMap.rows; ++i)
    {
        const uchar* rowPtr = cornerMap.ptr<uchar>(i);
        for (int j = 0; j < cornerMap.cols; ++j)
        {
            //if it is a feature point
            if (rowPtr[j])
            {
                points.push_back(cv::Point(j,i));
            }
        }
    }

    std::vector<cv::Point>::const_iterator it = points.begin();

    //for all corners
    while(it!=points.end()){
        //draw a circle at each corner location
        cv::circle(image, *it, radius, color, thickness);
        ++it;
    }
    
    return image;
}