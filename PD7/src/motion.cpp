#include <stdio.h>
#include <opencv2/legacy/legacy.hpp>
#include <cv.h>
#include <highgui.h> 

int main(int argc, char const *argv[])
{
    CvCapture* capture = cvCaptureFromFile("Bsb-EPGU.mov");

    IplImage* curFrame = cvQueryFrame(capture);
    IplImage* curFrame_bw;
    IplImage* velx = 0; 
    IplImage* vely = 0;

    double dx, dy;

    CvTermCriteria IterCriteria;
    IterCriteria.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
    IterCriteria.max_iter = 100;
    IterCriteria.epsilon = 0.01;

    velx = cvCreateImage(cvGetSize(curFrame),IPL_DEPTH_32F, 1); 
    vely = cvCreateImage(cvGetSize(curFrame),IPL_DEPTH_32F, 1); 

    while(1) {
        IplImage* nextFrame = cvQueryFrame(capture);
        if(!nextFrame) break;
        IplImage* nextFrame_bw;

        curFrame_bw = cvCreateImage(cvGetSize(curFrame),IPL_DEPTH_8U, 1); 
        nextFrame_bw = cvCreateImage(cvGetSize(nextFrame),IPL_DEPTH_8U, 1); 
         
        cvCvtColor(nextFrame, nextFrame_bw, CV_RGB2GRAY); 
        cvCvtColor(curFrame, curFrame_bw, CV_RGB2GRAY); 
        
        cvCalcOpticalFlowHS(curFrame_bw, nextFrame_bw, 0, velx, vely, 100, IterCriteria);

        for (int i = 0; i < curFrame_bw->width; i = i + 8)
        {
            for (int j = 0; j < curFrame_bw->height; j = j + 8)
            {
                dx = cvGetReal2D(velx, j, i);
                dy = cvGetReal2D(vely, j, i); 
                cvLine(curFrame_bw, cvPoint(i, j), cvPoint(i + dx, j + dy), cvScalar(255, 0, 0), 1, 8, 0);
            }
        }

        cvNamedWindow("Image 1bw:", 1); 
        cvNamedWindow("velx:", 1); 
        cvNamedWindow("vely:", 1); 
        
        cvShowImage("Image bw:", curFrame_bw); 
        cvShowImage("velx:", velx); 
        cvShowImage("vely:", vely); 
        
        curFrame = nextFrame; 
        if(cvWaitKey(10) == 27) break;
  }


        cvDestroyWindow("Image 1bw:"); 
        cvDestroyWindow("velx:"); 
        cvDestroyWindow("vely:"); 
        cvReleaseImage(&velx); 
        cvReleaseImage(&vely); 
    return 0;
}