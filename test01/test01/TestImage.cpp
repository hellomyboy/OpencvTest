#include <opencv2/opencv.hpp>
#include "TestImage.h"

void TestImage::resizeTest()
{
	double fScale = 0.314;
	CvSize cvSize;

	IplImage* pSrcImage =  cvLoadImage("res/02/lena.jpg", CV_LOAD_IMAGE_UNCHANGED);
	IplImage* pDesImage = NULL;

	cvSize.width = pSrcImage->width * fScale;
	cvSize.height = pSrcImage->height * fScale;

	pDesImage = cvCreateImage(cvSize, pSrcImage->depth, pSrcImage->nChannels);
	cvResize(pSrcImage, pDesImage, CV_INTER_AREA);

	cvNamedWindow("原图", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("缩放图", CV_WINDOW_AUTOSIZE);

	cvShowImage("原图", pSrcImage);
	cvShowImage("缩放图", pDesImage);
	cvSaveImage("res/02/缩放后图.jpg", pDesImage);

	cvDestroyWindow("原图");
	cvDestroyWindow("缩放图");
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pDesImage);
}
