#include "pd3.hpp"

int main(int argc, char const *argv[])
{
    cv::Mat imgR, imgL, templR, templL;
    std::vector<cv::Point> points;
    uchar *pntR, *pntL;
    int template_size;

    if (argc!=3){
        std::cout<<"Insert 2 arguments"<<std::endl;
        return -1;
    }

    imgL = cv::imread(argv[1]);
    imgR = cv::imread(argv[2]);

    std::cout<<"Template size: ";
    std::cin>>template_size;

    while(template_size % 2 == 0){
    	std::cout<<"Insert an odd number."<<std::endl;
    	std::cout<<"Template size: ";
    	std::cin>>template_size;

    }
    cv::cvtColor(imgL, imgL, CV_BGR2GRAY);
    cv::cvtColor(imgR, imgR, CV_BGR2GRAY);
    std::vector<int> sadValues;
    for (int i = template_size; i < imgL.rows - template_size; ++i){
        printf("i = %d \n", i);
        pntL = imgL.ptr<uchar>(i);
        pntR = imgR.ptr<uchar>(i);
        for (int j = template_size; j < imgR.cols - template_size; ++j){
            templL = template_creator(imgL, template_size, cv::Point(i,j));
            for (int k = template_size; k < imgR.cols - template_size; ++k){
                templR = template_creator(imgR, template_size, cv::Point(i,k));
                sadValues.push_back(cmptemplate(templL,templR));
            }
            sadValues.clear();
        }
    }
    
    return 0;
}
