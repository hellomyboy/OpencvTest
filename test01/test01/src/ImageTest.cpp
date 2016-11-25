
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void test_image_process()
{
	//图像的载入与显示
	string girlpic = "res/01/girl.png";
	Mat pic = imread(girlpic);
	namedWindow("girl");
	imshow("girl", pic);

	//混合
	Mat dota = imread("res/01/dota2.png", 199);
	Mat logo = imread("res/01/logo.png");
	namedWindow("dota");
	imshow("dota", dota);

	namedWindow("logo");
	imshow("logo", logo);

	//------------------
	Mat imageROI;
	imageROI = dota(Rect(800, 350, logo.cols, logo.rows));
	//imageROI = image(Rect(800, 350, logo.cols, logo.rows));

	// 将logo加到原图上
	addWeighted(imageROI, 0.5, logo, 0.3, 0.0, imageROI);
	namedWindow("newpic");
	imshow("newpic", dota);

	//将图片保存下来
	imwrite("res/01/newpic.jpg", dota);
}


void roi_addimage()
{
	Mat image1 = imread("res/01/dota2.png");
	Mat image2 = imread("res/01/logo.png");

	if (!image1.data) {
		printf("res/01/dota.png not exist");
		return;
	}
	if (!image2.data) {
		printf("res/01/logo.png not exist");
		return;
	}

	Mat imgROI = image1(Rect(200,100, image2.cols, image2.rows));
	Mat mask = imread("res/01/logo.png", 0);
	image2.copyTo(imgROI, mask);

	namedWindow("roi_add_image");
	imshow("roi_add_image", image1);
}

void LinearBlending()
{
	double alphaValue = 0.4;
	double betaValue = 1 - alphaValue;
	Mat image1, image2, dstImage;

	image1 = imread("res/01/mogu.jpg");
	if (!image1.data) {
		printf("res/01/mogu.jpg not exist");
		return;
	}
	image2 = imread("res/01/rain.jpg");
	if (!image2.data) {
		printf("res/01/rain.jpg not exist");
		return;
	}

	addWeighted(image1, alphaValue, image2, betaValue, 0.0, dstImage);

	namedWindow("origin");
	imshow("origin", image1);

	namedWindow("blendpic");
	imshow("blendpic", dstImage);
}

void loadImgSimpleTest(char* filename)
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