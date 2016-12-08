#include <opencv2/opencv.hpp>
#include "TestImage.h"

#include <iostream>
#include <iomanip>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/legacy/compat.hpp>

using namespace cv;

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

IplImage* g_pSrcImage, *g_pCannyImg;
const char* pstrWindowCannyTitle = "Canny��Ե���";

void on_trackbar_cb(int threshold)
{
	cvCanny(g_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvShowImage(pstrWindowCannyTitle, g_pCannyImg);
}

void TestImage::cannyTest()
{
	//const char* pstrSrcImageName = "res/02/lena.jpg";
	const char* pstrSrcImageName = "res/01/girl.png";
	const char* pstrWindowSrcTitle = "ԭͼ";
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
	cvShowImage("��ֵͼ��", pBinaryImage);
}

// ��ֵͼ�����
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

	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ", pSrcImage);
	cvNamedWindow("��ֵͼ��", CV_WINDOW_AUTOSIZE);

	int nThreshold = 0;
	cvCreateTrackbar("trackbar", "��ֵͼ��", &nThreshold, 254, binaryimage_trackbar_callback);
	binaryimage_trackbar_callback(1);

	cvWaitKey(1);
	//cvDestroyWindow("ԭͼ");
	//cvDestroyWindow("��ֵͼ��");
	//cvReleaseImage(&pSrcImage);
	//cvReleaseImage(&pGrayImage);
	//cvReleaseImage(&pBinaryImage);
}

int TestImage::imageCombineTest()
{
	Mat leftImg = imread("res/03/left.jpg");

	Mat rightImg = imread("res/03/right.jpg");

	if (leftImg.data == NULL || rightImg.data == NULL)

		return 0;

	//ת���ɻҶ�ͼ

	Mat leftGray;

	Mat rightGray;

	cvtColor(leftImg, leftGray, CV_BGR2GRAY);

	cvtColor(rightImg, rightGray, CV_BGR2GRAY);



	//��ȡ����ͼ��Ĺ�ͬ������

	int minHessian = 400;

	SurfFeatureDetector detector(minHessian);

	vector<KeyPoint> leftKeyPoints, rightKeyPoints;

	detector.detect(leftGray, leftKeyPoints);

	detector.detect(rightGray, rightKeyPoints);

	SurfDescriptorExtractor extractor;

	Mat leftDescriptor, rightDescriptor;

	extractor.compute(leftGray, leftKeyPoints, leftDescriptor);

	extractor.compute(rightGray, rightKeyPoints, rightDescriptor);

	FlannBasedMatcher matcher;

	vector<DMatch> matches;

	matcher.match(leftDescriptor, rightDescriptor, matches);

	int matchCount = leftDescriptor.rows;

	if (matchCount>15)

	{

		matchCount = 15;

		//sort(matches.begin(),matches.begin()+leftDescriptor.rows,DistanceLessThan);

		sort(matches.begin(), matches.begin() + leftDescriptor.rows);

	}

	vector<Point2f> leftPoints;

	vector<Point2f> rightPoints;

	for (int i = 0; i<matchCount; i++)

	{

		leftPoints.push_back(leftKeyPoints[matches[i].queryIdx].pt);

		rightPoints.push_back(rightKeyPoints[matches[i].trainIdx].pt);

	}



	//��ȡ���ͼ���ұ�ͼ���ͶӰӳ���ϵ

	Mat homo = findHomography(leftPoints, rightPoints);

	Mat shftMat = (Mat_<double>(3, 3) << 1.0, 0, leftImg.cols, 0, 1.0, 0, 0, 0, 1.0);



	//ƴ��ͼ��

	Mat tiledImg;

	warpPerspective(leftImg, tiledImg, shftMat*homo, Size(leftImg.cols + rightImg.cols, rightImg.rows));

	rightImg.copyTo(Mat(tiledImg, Rect(leftImg.cols, 0, rightImg.cols, rightImg.rows)));



	//����ͼ��

	imwrite("res/03/tiled.jpg", tiledImg);



	//��ʾƴ�ӵ�ͼ��

	imshow("tiled image", tiledImg);

	waitKey(0);

	return 0;
}
