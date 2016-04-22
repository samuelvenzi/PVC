#include <cv.h>
#include <highgui.h>
#include <stdio.h>

double gettime();

int main()
{
  IplImage *cvImg; // Objeto usado para armazenar a imagem
  CvSize imgSize; 
  int i1 = 0, j1 = 0;
  double t;
  imgSize.width = 4320; 
  imgSize.height = 1280;  
  double start = gettime();
  cvImg = cvCreateImage( imgSize, 8, 1 );
  for ( i1 = 0; i1 < imgSize.width; i1++ )
    for ( j1 = 0; j1 < imgSize.height; j1++ )
      ((uchar*)(cvImg->imageData + cvImg->widthStep*j1))[i1] = (char)((i1 * j1)%256);
  cvNamedWindow( "Abrindo a Imagem Gerada...", 1 );
  cvShowImage( "Abrindo a Imagem Gerada...", cvImg );
  double stop = gettime();
  t = stop - start;
  cvWaitKey(10);
  cvDestroyWindow( "image" );
  cvReleaseImage( &cvImg );
  printf("Tempo de execução: %f\n", t);
  return 0;
}

double gettime(){
	struct timespec t;

	if(clock_gettime(CLOCK_REALTIME, &t) != 0)
		return 0;
	return (t.tv_sec + (t.tv_nsec/1000000000.0));
}