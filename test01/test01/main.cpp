#include <cv.h>
#include <highgui.h>
using namespace std;

void guitest(char* filename)
{
	cvNamedWindow("win1", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("win1", 100, 100);

	IplImage* img = 0;
	img = cvLoadImage(filename);
	if (!img) {
		printf("cannot load image file: %s\n", filename);
	}

	cvShowImage("win1", img);
	cvWaitKey(0);
	cvDestroyWindow("win1");
}

void videotest()
{
	CvCapture* capture = cvCaptureFromCAM(0);
}

int main()
{
	guitest("C:\\Users\\think\\Desktop\\terrain.jpg");
	return 0;
}

int test01()
{
	IplImage * test;
	test = cvLoadImage("‪C:\\Users\\think\\Desktop\\leaf01.png");//图片路径
	cvNamedWindow("test_demo", 1);
	cvShowImage("test_demo", test);
	cvWaitKey(0);
	cvDestroyWindow("test_demo");
	cvReleaseImage(&test);
	return 0;
}