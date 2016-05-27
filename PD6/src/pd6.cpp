#include "pd6.hpp"

//compute Harris corners
void DetectCorners(const cv::Mat& image){
    cv::Mat cornerStrength;
    cv::cornerHarris(image, cornerStrength,
        3,  //neighborhood size
        3,  //aperture size
        0.01); //Harris parameter
    //internal threshold computation
    double minStrength; //not used
    cv::minMaxLoc(cornerStrength, &minStrength, &maxStrength);
    //local maxima detection
    cv::Mat dilated; //temporary image
    cv::dilate(cornerStrength, dilated, cv::Mat());
    cv::compare(cornerStrength, dilated, localMax, cv::CMP_EQ);

}

//Get corner map from the computed Harris values
cv::Mat getCornerMap(double qualityLevel){
    cv::Mat cornerMap;

    //thresholding the corner strength
    threshold = qualityLevel*maxStrength;
    cv::threshold(cornerStrength, cornerTh, threshold, 255, cv::THRESH_BINARY);

    //convert to 8-bit image
    cornerTh.convertTo(cornerMap,CV_8U);
    //non-maxima supression
    cv::bitwise_and(cornerMap,localMax,cornerMap);

    return cornerMap;
}

//Get the feature points from the computed corner map
void getCorners(std::vector<cv::Point> &points, const cv::Mat& cornerMap){
    //iterate over the pixels to obtain all features
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
}

//Draw circles at feature point locations on an image
void drawOnImage(cv::Mat &image, const std::vector<cv::Point> &points,
                cv::Scalar color = cv::Scalar(255,255,255),
                int radius = 3, int thickness = 2){

    std::vector<cv::Point>::const_iterator it = points.begin();

    //for all corners
    while(it!=points.end()){
        //draw a circle at each corner location
        cv::circle(image, *it, radius, color, thickness);
        ++it;
    }
}