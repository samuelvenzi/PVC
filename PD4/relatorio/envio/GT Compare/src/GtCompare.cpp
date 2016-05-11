#include "groudtruth.hpp"

int main(int argc, char const *argv[])
{
    cv::Mat gt_img;
    cv::Mat c_img, s_img, l_img;
    double canny_precision, sobel_precision, laplacian_precision;
    int img_number;

    std::cout<<"Number of image: ";
    std::cin>>img_number;

    gt_img = cv::imread(argv[1]);
    c_img = cv::imread(argv[2]);
    s_img = cv::imread(argv[3]);
    l_img = cv::imread(argv[4]);

    for (int i = 0; i < gt_img.rows; ++i)
    {
        for (int j = 0; j < gt_img.cols; ++j)
        {
            gt_img.at<uchar>(i,j) = 255 - gt_img.at<uchar>(i,j);
        }
    }

    canny_precision = gtcompare(gt_img, c_img);
    sobel_precision = gtcompare(gt_img, s_img);
    laplacian_precision = gtcompare(gt_img, l_img);

    std::ofstream myfile;
    myfile.open ("Method_Precision.txt", std::ios::app);
    myfile<<"Image number: "<<img_number<<std::endl;
    myfile<<"Method Canny: "<<canny_precision<<std::endl;
    myfile<<"Method Sobel: "<<sobel_precision<<std::endl;
    myfile<<"Method Laplacian: "<<laplacian_precision<<std::endl;
    myfile<<"\n\n";
    myfile.close();

    return 0;
}