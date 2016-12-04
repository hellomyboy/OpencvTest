#include <cv.h>
#include <highgui.h>
#include "TestImage.h"
using namespace std;

extern void test_image_process();
extern void roi_addimage();
extern void LinearBlending();

extern int testLoadPic();


int main(int argc, char** argv)
{
	//cout << argc << endl;
	//cout << argv[0] << endl;

	//test_image_process();
	//roi_addimage();
	// LinearBlending();

	//testLoadPic();

	TestImage image;
	image.resizeTest();

	cvWaitKey(0);
	return 0;
}

