#include "pd6.hpp"

int main(int argc, char const *argv[])
{

    cv::VideoCapture capture(0);
    cv::Mat frame, frame2, frame3;
    double threshold;

    std::cout<<"Threshold value:";
    std::cin>>threshold;

    /*if (argc != 2)
    {
        std::cout<<"Insert parameter."<<std::endl;
        return -1;
    }
    cv::Mat image;
    cv::Mat image2;
    image = cv::imread(argv[1]);
    image2 = cv::imread(argv[1]);
    cv::cvtColor(image, image, CV_BGR2GRAY);
    cv::cvtColor(image2, image2, CV_BGR2GRAY);*/
    
    cv::SurfFeatureDetector surf(2500.);
    std::vector<cv::KeyPoint> keypoints;


    while(true){
        capture >> frame;
        capture >> frame2;
        capture >> frame3;
        cv::cvtColor(frame, frame, CV_BGR2GRAY);
        cv::cvtColor(frame2, frame2, CV_BGR2GRAY);
        cv::cvtColor(frame3, frame3, CV_BGR2GRAY);
        cv::Mat cornerImage;
        cornerImage = DetectCorners(frame, threshold);

        frame2 = GoodFeatures(frame2);

        surf.detect(frame3,keypoints);
        cv::drawKeypoints(frame3, keypoints, frame3,
                            cv::Scalar(255,255,255),
                            cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);


        cv::imshow("Harris corners", cornerImage);
        cv::imshow("Good Features", frame2);
        cv::imshow("Surf", frame3);
        if(cv::waitKey(30) >= 0) break;
    }


    return 0;
}