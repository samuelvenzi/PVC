#include "pd4.hpp"

int main(int argc, char const *argv[])
{
    cv::Mat source_img, bw_img, dst;
    int low_threshold;
    source_img = cv::imread(argv[1]);
    std::cout<<"Threshold value: ";
    std::cin>>low_threshold;

    dst.create(source_img.size(), source_img.type());
    cv::cvtColor(source_img, bw_img, CV_BGR2GRAY);

    
    Canny_Detection(bw_img, source_img, dst, low_threshold);
    Sobel_Detection(bw_img, source_img);
    Laplacian_Detection(bw_img, source_img);

    return 0;
}