#include "pd4.hpp"

void Canny_Detection(cv::Mat bw_img, cv::Mat source_img, cv::Mat dst, int low_threshold){
    cv::Mat edges;
    int ratio = 3, kernel_size = 3;
    cv::blur(bw_img, edges, cv::Size(3,3));
    cv::Canny(edges, edges, low_threshold, low_threshold*ratio, kernel_size);

    dst = cv::Scalar::all(0);
    source_img.copyTo(dst,edges);
    cv::imwrite("../img_canny.jpg", dst);
    cv::imshow("Canny", dst);
    cv::waitKey(0);
}

void Sobel_Detection(cv::Mat bw_img, cv::Mat source_img){
    cv::Mat grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    cv::GaussianBlur(source_img, source_img, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT);
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;

    cv::cvtColor(source_img, bw_img, CV_BGR2GRAY);

    cv::Sobel(bw_img, grad_x, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::Sobel(bw_img, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT);
    cv::convertScaleAbs(grad_y, abs_grad_y);
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    cv::imwrite("../img_sobel.jpg", grad);
    cv::imshow("Sobel", grad);
    cv::waitKey(0);
}

void Laplacian_Detection(cv::Mat bw_img, cv::Mat source_img){
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    cv::Mat dst;

    cv::GaussianBlur(source_img, source_img, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT);
    cv::cvtColor(source_img, bw_img, CV_BGR2GRAY);
    cv::Mat abs_dst;

    cv::Laplacian(bw_img, dst, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT);
    convertScaleAbs(dst, abs_dst);
    cv::imwrite("../img_laplacian.jpg",abs_dst);
    cv::imshow("Laplacian", abs_dst);
    cv::waitKey(0);



}