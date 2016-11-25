#include "cv.h"
#include "highgui.h"
#include <opencv2\legacy\legacy.hpp>

using namespace cv;

int testLoadPic() 
{
	char* picname = "res/02/lena.jpg";
	CvImage img(picname, 0, CV_LOAD_IMAGE_COLOR);
	CvImage img_yuv, y, noise;

	CvRNG rng = cvRNG(-1);
	if (!img.data()) {	//if the image data has loaded
		std::cerr << picname << " not exist" << std::endl;
		return -1;
	}

	img_yuv = img.clone();
	cvCvtColor(img, img_yuv, CV_BGR2YCrCb);  //色彩空间转换
	y.create(img.size(), IPL_DEPTH_8U, 1);
	noise.create(img.size(), IPL_DEPTH_32F, 1);

	cvSplit(img_yuv, y, 0, 0, 0);
	//正态分布的随机数组
	cvRandArr(&rng, noise, CV_RAND_NORMAL, cvScalarAll(0), cvScalarAll(20));
	cvSmooth(noise, noise, CV_GAUSSIAN, 5, 5, 1, 1);	//高斯滤波做平衡
	cvAcc(y, noise);
	cvConvert(noise, y);
	cvMerge(y, 0, 0, 0, img_yuv);	//图层合并
	cvCvtColor(img_yuv, img, CV_YCrCb2BGR);  //图像色彩空间转换
		
	cvNamedWindow("win", CV_WINDOW_AUTOSIZE);
	img.show("win");
	cvWaitKey();

	return 0;
}