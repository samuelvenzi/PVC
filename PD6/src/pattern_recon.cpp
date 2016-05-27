#include "pd6.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout<<"Insert parameter."<<std::endl;
        return -1;
    }
    cv::Mat image;
    image = cv::imread(argv[1]);
    cv::cvtColor(image, image, CV_BGR2GRAY);

    cv::Mat cornerImage;
    cornerImage = DetectCorners(image);

    cv::imshow("Harris corners", cornerImage);
    cv::waitKey(0); 

    return 0;
}