#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void CallBackFunc(int event, int x, int y, int flags, void* ptr){
	if (event == EVENT_LBUTTONDOWN){
		vector<Point>*p = (vector<Point>*)ptr;
   		p->push_back(Point(x,y));
	}
	
}

void GetDistance(void* points){
	float distance;
	vector<Point>*p = (vector<Point>*)points;
	Point diff = p->at(0) - p->at(1);
	distance = sqrt(diff.x*diff.x + diff.y*diff.y);
	cout<<"Distância entre os pontos é: "<<distance<<endl;
}


int main(int argc, char const *argv[])
{
	vector<Point> points;
	int height = 500, width = 500;
	int i, j;
	bool click = false;

	Mat img(height, width, CV_8U);
	namedWindow("My Window", 1);

	while(!click){
		imshow("My Window", img); 
		waitKey(100);
		setMouseCallback("My Window", CallBackFunc, (void*)&points);
		if (points.size() == 2)
		{
			line(img, points.at(0), points.at(1), Scalar(255, 255, 255));
			destroyWindow("My Window");
			click = true;
		}
	}
	waitKey(100);
	GetDistance((void*)&points);
	imshow("Line", img);
	waitKey(0);
	return 0;
}