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

IplImage* g_pSrcImage, *g_pCannyImg;
const char* pstrWindowCannyTitle = "Canny边缘检测";

void on_trackbar_cb(int threshold)
{
	cvCanny(g_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvShowImage(pstrWindowCannyTitle, g_pCannyImg);
}

void TestImage::cannyTest()
{
	//const char* pstrSrcImageName = "res/02/lena.jpg";
	const char* pstrSrcImageName = "res/01/girl.png";
	const char* pstrWindowSrcTitle = "原图";
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

IplImage* pGrayImage = NULL, *pBinaryImage = NULL;
void binaryimage_trackbar_callback(int pos)
{
	cvThreshold(pGrayImage, pBinaryImage, pos, 255, CV_THRESH_BINARY);
	cvShowImage("二值图像", pBinaryImage);
}

// 二值图像测试
void TestImage::binaryImageTest()
{
	const char* imagePath = "res/01/girl.png";
	IplImage* pSrcImage = cvLoadImage(imagePath, CV_LOAD_IMAGE_UNCHANGED);
	pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY); 

	pBinaryImage = cvCreateImage(cvGetSize(pGrayImage), IPL_DEPTH_8U, 1);

	//std::cout << "size(srcImage):" << cvGetSize(pSrcImage).width << "," << cvGetSize(pSrcImage).height << std::endl;
	//std::cout << "size(grayImage):" << cvGetSize(pGrayImage).width << "," << cvGetSize(pGrayImage).height << std::endl;
	//std::cout << "size(binaryImage):" << cvGetSize(pBinaryImage).width << "," << cvGetSize(pBinaryImage).height << std::endl;
	std::cout << "depth:" << pSrcImage->depth << "," << pGrayImage->depth << "," << pBinaryImage->depth << std::endl;

	cvNamedWindow("原图", CV_WINDOW_AUTOSIZE);
	cvShowImage("原图", pSrcImage);
	cvNamedWindow("二值图像", CV_WINDOW_AUTOSIZE);

	int nThreshold = 0;
	cvCreateTrackbar("trackbar", "二值图像", &nThreshold, 254, binaryimage_trackbar_callback);
	binaryimage_trackbar_callback(1);

	cvWaitKey(1);
	//cvDestroyWindow("原图");
	//cvDestroyWindow("二值图像");
	//cvReleaseImage(&pSrcImage);
	//cvReleaseImage(&pGrayImage);
	//cvReleaseImage(&pBinaryImage);
}
