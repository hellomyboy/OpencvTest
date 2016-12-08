#include "InputManager.h"

void on_mousechange(int evnt, int x, int y, int flags, void* param)
{
	static bool isMouseDown = false;
	static CvPoint prePoint = cvPoint(0, 0);
	static InputManager inputManager = *((InputManager*)(param));

	switch (evnt)
	{
	case CV_EVENT_LBUTTONDOWN:
		isMouseDown = true;
		prePoint = cvPoint(x, y);
		break;

	case CV_EVENT_LBUTTONUP:
		isMouseDown = false;
		break;

	case CV_EVENT_MOUSEMOVE:
		if (isMouseDown)
		{
			CvPoint curPoint = cvPoint(x, y);
			cvDrawLine(inputManager.pSrcImage, prePoint, curPoint, CV_RGB(20, 20, 20), 2);
			prePoint = curPoint;
			cvShowImage(inputManager.pstrWindowDrawTitle, inputManager.pSrcImage);
		}
		break;
	}
}

InputManager::InputManager(): 
	pstrWindowDrawTitle("Êó±ê»æÍ¼"),
	pstrSaveImageName("res/02/mouseevent.jpg"),
	maxWidth(500), 
	maxHeight(400)
{
}

InputManager::~InputManager()
{
	cvReleaseImage(&pSrcImage);
	cvDestroyWindow(pstrWindowDrawTitle);
}

void InputManager::run()
{
	pSrcImage = cvCreateImage(cvSize(maxWidth, maxHeight), IPL_DEPTH_8U, 3);
	cvSet(pSrcImage, CV_RGB(255, 255, 255));
	cvNamedWindow(pstrWindowDrawTitle, CV_WINDOW_AUTOSIZE);
	cvShowImage(pstrWindowDrawTitle, pSrcImage);

	cvSetMouseCallback(pstrWindowDrawTitle, on_mousechange, this);
	int c;
	do {
		c = cvWaitKey(0);
		switch (c)
		{
		case 'r':
			cvSet(pSrcImage, CV_RGB(255, 255, 255));
			cvShowImage(pstrWindowDrawTitle, pSrcImage);
			break;
		case 's':
			cvSaveImage(pstrSaveImageName, pSrcImage);
			break;
		default:
			break;
		}
	} while (c > 0 && c != 27);
}

