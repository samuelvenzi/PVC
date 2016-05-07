#include "pd3.hpp"

int main(int argc, char const *argv[])
{
    cv::Mat imgR, imgL, templR, templL;
    std::vector<cv::Point> points;
    uchar *pntR, *pntL;
    int template_size;

    if (argc!=3){
        std::cout<<"Insert 2 arguments"<<std::endl; //the arguments are two stereoscopic images
        return -1;
    }

    imgL = cv::imread(argv[1]);     //read each image
    imgR = cv::imread(argv[2]);

    std::cout<<"Template size: ";   //template size should be always odd so that it has a central element
    std::cin>>template_size;
    while(template_size % 2 == 0){
    	std::cout<<"Insert an odd number."<<std::endl;
    	std::cout<<"Template size: ";
    	std::cin>>template_size;
    }

    cv::cvtColor(imgL, imgL, CV_BGR2GRAY);  //convert image to grayscale
    cv::cvtColor(imgR, imgR, CV_BGR2GRAY);

    int sad, new_sad, XR = 0, XL = 0, Z, X, Y;
    cv::Mat depth(imgL.rows, imgL.cols, CV_8U);
    for (int i = template_size; i < imgL.rows - template_size; ++i)   //change the row we're are looking into
    { 
        printf("i = %d \n", i);
        sad = INT_MAX;
        pntL = imgL.ptr<uchar>(i);  //pointers for each image
        pntR = imgR.ptr<uchar>(i);
        
        for (int j = template_size; j < imgR.cols - template_size; ++j)  //fix columns on the left image
        {    
            sad = INT_MAX;
           templL = template_creator(imgL, template_size, cv::Point(i,j));
            
            for (int k = template_size; k < j; ++k)
            {
                templR = template_creator(imgR, template_size, cv::Point(i,k));
                new_sad = cmptemplate(templL, templR);
                if(new_sad < sad){  
                    sad = new_sad;
                    XL = j;
                    XR = k;
                }
            } 
        
            if((XL - XR) != 0){
                Z = 3000/(XL - XR);
                X = 120*(XL + XR)/(2*(XL - XR));
                Y = 120*(i)/((XL - XR));
            }
            else
                Z = 3000;
            
            depth.at<uchar>(i,j) = Z;
        }
    }
    cv::imwrite( "../../aloe-depth.jpg", depth);
    char key = 'e';
    while(key != 'q'){
        cv::imshow("Depth Map", depth);
        key = cv::waitKey(0);
    }   

    return 0;
}
