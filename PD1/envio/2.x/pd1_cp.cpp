#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <time.h>

double gettime();

int main(int argc, char const *argv[])
{
	int i, j;
	double start, stop, t;
	int width = 4320, height = 1280;
	start = gettime();
	cv::Mat img(height, width, CV_8U);
	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			img.at<uchar>(i,j) = (char)(i*j)%256;
		}
	}
	stop = gettime();
	//imshow("Imagem gerada", img);
	t = stop - start;
	cv::waitKey(0);
	printf("Tempo de execução: %f segundos\n",t);
	return 0; 
}

double gettime(){
	struct timespec t;
	if(clock_gettime(CLOCK_REALTIME, &t) != 0)
		return 0;
	return (t.tv_sec + (t.tv_nsec/1000000000.0));
}