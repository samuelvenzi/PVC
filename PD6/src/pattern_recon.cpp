#include "pd6.hpp"

int main(int argc, char const *argv[])
{

    cv::VideoCapture capture(0);
    std::vector<cv::Point> points;
    cv::Mat frame, frame2, flipped;

/*
    double threshold;
    std::cout<<"Threshold value:";
    std::cin>>threshold;
    if (argc != 2)
    {
        std::cout<<"Insert parameter."<<std::endl;
        return -1;
    }
    cv::Mat image;
    cv::Mat image2;
    image = cv::imread(argv[1]);
    image2 = cv::imread(argv[1]);
    cv::cvtColor(image, image, CV_BGR2GRAY);
    cv::cvtColor(image2, image2, CV_BGR2GRAY);
*/
    
    cv::SurfFeatureDetector surf(2500.);
    std::vector<cv::KeyPoint> keypoints, temp_keypoints;

    cv::SurfDescriptorExtractor extractor;
    cv::Mat descriptor, temp_descriptor;

    cv::BFMatcher matcher(cv::NORM_L2);
    std::vector<cv::DMatch> matches;
    cv::Mat temp(100, 100, CV_8UC1);

    cv::namedWindow("Select object", 1);
    bool clicked = false;

    while(!clicked){

        capture >> frame;
        cv::flip(frame, flipped, 1);
        cv::cvtColor(flipped, flipped, CV_BGR2GRAY);
        
        cv::imshow("Select object", flipped);
        cv::waitKey(100);
        
        cv::setMouseCallback("Select object", CallBackFunc, (void*)&points);

        if(points.size() == 1){
            temp = template_creator(flipped, 200, points.at(0));
            clicked = true;
            cv::destroyWindow("Select object");
        }
    }

    cv::imshow("Template", temp);
    cv::imshow("Capture", flipped);
    cv::waitKey(0);

    while(true){
        capture >> frame;
        cv::cvtColor(frame, frame, CV_BGR2GRAY);
        cv::flip(frame, flipped, 1);
        
        cv::waitKey(10);

        surf.detect(flipped,keypoints);
        surf.detect(temp, temp_keypoints);

        extractor.compute(flipped, keypoints, descriptor);
        extractor.compute(temp, temp_keypoints, temp_descriptor);

        matcher.match(temp_descriptor, descriptor, matches);

        //std::nth_element(matches.begin(), matches.begin() +1, matches.end());
        //matches.erase(matches.begin()+2, matches.end());

        //cv::Mat img_matches;
        //cv::drawMatches(temp, temp_keypoints, flipped, keypoints, matches, img_matches);  

        std::vector<cv::Point> pts;
        
        for (uint i = 0; i < matches.size(); ++i)
        {
            int idx2 = matches[i].trainIdx;
            pts.push_back(keypoints[idx2].pt);
        }

        long int x = 0, y = 0;
        for (uint i = 0; i < pts.size(); ++i)
        {
            x += pts[i].x;
            y += pts[i].y;
        }
        x = x/pts.size();
        y = y/pts.size();

        cv::Point pos, pos2;
        pos.x = x - 100;
        pos.y = y - 100;
        pos2.x = x + 100;
        pos2.y = y + 100;
        cv::rectangle(flipped, pos, pos2, cv::Scalar(255,255,255), 2);


        cv::imshow("Match", flipped);
        if(cv::waitKey(30) >= 0) break;
    }

    return 0;


}