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

	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("����ͼ", CV_WINDOW_AUTOSIZE);

	cvShowImage("ԭͼ", pSrcImage);
	cvShowImage("����ͼ", pDesImage);
	cvSaveImage("res/02/���ź�ͼ.jpg", pDesImage);

	cvDestroyWindow("ԭͼ");
	cvDestroyWindow("����ͼ");
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pDesImage);
}
