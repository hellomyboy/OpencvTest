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

	cvNamedWindow("‘≠Õº", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Àı∑≈Õº", CV_WINDOW_AUTOSIZE);

	cvShowImage("‘≠Õº", pSrcImage);
	cvShowImage("Àı∑≈Õº", pDesImage);
	cvSaveImage("res/02/Àı∑≈∫ÛÕº.jpg", pDesImage);

	cvDestroyWindow("‘≠Õº");
	cvDestroyWindow("Àı∑≈Õº");
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&pDesImage);
}

IplImage* g_pSrcImage, *g_pCannyImg;
const char* pstrWindowCannyTitle = "Canny±ﬂ‘µºÏ≤‚";

void on_trackbar_cb(int threshold)
{
	cvCanny(g_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvShowImage(pstrWindowCannyTitle, g_pCannyImg);
}

void TestImage::cannyTest()
{
	//const char* pstrSrcImageName = "res/02/lena.jpg";
	const char* pstrSrcImageName = "res/01/girl.png";
	const char* pstrWindowSrcTitle = "‘≠Õº";
	const char* pstrWindowToolBar = "Threshold";

	g_pSrcImage = cvLoadImage(pstrSrcImageName, CV_LOAD_IMAGE_GRAYSCALE);
	g_pCannyImg = cvCreateImage(cvGetSize(g_pSrcImage), IPL_DEPTH_8U, 1);

	cvNamedWindow(pstrWindowSrcTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowCannyTitle, CV_WINDOW_AUTOSIZE);

	int nThreasholdEge = 1;
	cvCreateTrackbar(pstrWindowToolBar, pstrWindowCannyTitle, &nThreasholdEge, 100, on_trackbar_cb);

	cvShowImage(pstrWindowSrcTitle, g_pSrcImage);
	on_trackbar_cb(1);

	cvWaitKey();
	/*cvDestroyWindow(pstrWindowSrcTitle);
	cvDestroyWindow(pstrWindowCannyTitle);*/
	cvReleaseImage(&g_pSrcImage);
	cvReleaseImage(&g_pCannyImg);
}
