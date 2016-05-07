#include "pd3.hpp"

cv::Mat template_creator(cv::Mat img, int template_size, cv::Point pos){
    cv::Mat templ(template_size, template_size, CV_8UC1);
    uchar* pointer;
    int x,y;

    for (int i = 0; i < template_size; ++i)
    {
        pointer = templ.ptr<uchar>(i);
        x = pos.x - (template_size - 2) + i;
        for (int j = 0; j < template_size; ++j)
        {
            y = pos.y - (template_size - 2) + j;
            pointer[j] = img.at<uchar>(x, y);
        }
    }

    return templ;
}

int cmptemplate(cv::Mat templL, cv::Mat templR){
	uchar *ptR, *ptL;
	int sad;

	sad = 0;

	for (int i = 0; i < templL.rows; ++i) {
		ptL = templL.ptr<uchar>(i);
		ptR = templR.ptr<uchar>(i);
		for (int j = 0; j < templL.cols; ++j) {
			sad = sad + abs(ptR[j] - ptL[j]);
		}
	}
	return sad;
}
