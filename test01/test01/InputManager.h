#pragma once
#include <opencv2/opencv.hpp>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void run();

//private:
	IplImage* pSrcImage;
	char* pstrWindowDrawTitle;
	char* pstrSaveImageName;

	int maxWidth, maxHeight;
};

