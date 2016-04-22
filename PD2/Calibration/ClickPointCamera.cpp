#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
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

void grid(Mat frame){
	for(int i = 0; i <= 640; i +=160){
		line(frame, Point(i, 0), Point(i, 480), Scalar(255, 0, 0));
		for(int j = 0; j < 480; j += 120)
			line(frame, Point(0, j), Point(640, j), Scalar(255, 0, 0));
	}
}


int main(int argc, char const *argv[])
{
	vector<Point> points;
	VideoCapture capture(0);
    Mat frame, distortion, intrinsics, mapx, mapy, img;
    bool click = false;
    int i, j;

	namedWindow("My Window", 1);
	
	capture >> frame;

	FileStorage fs_dist;
	fs_dist.open("Distortion.xml", FileStorage::READ);
	fs_dist["Distortion"] >> distortion;
	fs_dist.release();
	
	FileStorage fs_intr;
	fs_intr.open("Intrinsics.xml", FileStorage::READ);
	fs_intr["Intrinsics"] >> intrinsics;
	fs_intr.release();

	Mat R;
	mapx.create(frame.size(), CV_32FC1);
	mapy.create(frame.size(), CV_32FC1);

	//Tudo resolvido
	initUndistortRectifyMap(intrinsics, distortion, R, intrinsics, frame.size(), CV_32FC1, mapx, mapy);
	//Mas não sei que porras é matriz R


	while(!click){
		capture >> frame;
    	imshow("My Window", frame);
		waitKey(100);
		remap(frame, img, mapx, mapy, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0,0));
		grid(img);
		imshow("Undistort", img);
		setMouseCallback("Undistort", CallBackFunc, (void*)&points);
    	if(waitKey(1) >= 0){}
		if (points.size() == 2)
		{
			line(frame, points.at(0), points.at(1), Scalar(255, 255, 255));
			destroyWindow("Undistort");
			destroyWindow("My Window");
			click = true;
		}
	}

	waitKey(100);
	GetDistance((void*)&points);
	while(true){
		capture >> frame;
		remap(frame, img, mapx, mapy, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0,0));
		line(img, points.at(0), points.at(1), Scalar(255, 255, 255));
		grid(img);
		imshow("Undistort", img);
	    if(waitKey(1) >= 0){}
	}

		
  
  	return 0;
}
