#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;
using namespace cv;

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "cvaux.h"

int main2()
{
	IplImage* src = NULL;
	IplImage* floatsrc = NULL;
	IplImage* floathsv = NULL;
	IplImage* floatimgH = NULL;
	IplImage* floatimgS = NULL;
	IplImage* floatimgV = NULL;

	cvNamedWindow("src", 1);
	cvNamedWindow("H通道", 1);
	cvNamedWindow("S通道", 1);
	cvNamedWindow("V通道", 1);

	src = cvLoadImage("lena.jpg", -1);
	cvShowImage("src", src);
	CvSize size = cvGetSize(src);

	//先将图像转换成float型的
	floatsrc = cvCreateImage(size, IPL_DEPTH_32F, 3);
	floathsv = cvCreateImage(size, IPL_DEPTH_32F, 3);
	floatimgH = cvCreateImage(size, IPL_DEPTH_32F, 1);
	floatimgS = cvCreateImage(size, IPL_DEPTH_32F, 1);
	floatimgV = cvCreateImage(size, IPL_DEPTH_32F, 1);

	//将src从8位转换到32位的float型
	cvConvertScale(src, floatsrc, 1.0 / 255.0, 0);//归一化之后方能够显示
	//cvConvertScale( src, floatsrc, 1, 0 );
	//cvShowImage("floatsrc",floatsrc);
	//cvWaitKey(-1);

	//将float型图像 从BGR转换到HSV  如果需要转换到其他的颜色空间 那么改变CV_BGR2HSV即可
	//cvCvtColor要求两个参数的类型必须完全相同，所以要转为float型
	cvCvtColor(floatsrc, floathsv, CV_BGR2HSV);

	//将三通道图像 分解成3个单通道图像，H对应的通道时0，S、V对应的通道时1和2
	//cvCvtPixToPlane(picHSV, h_plane, s_plane, v_plane, 0);
	cvSplit(floathsv, floatimgH, floatimgS, floatimgV, NULL);

	cvShowImage("src", src);
	cvShowImage("H通道", floatimgH);
	cvShowImage("S通道", floatimgS);
	cvShowImage("V通道", floatimgV);
	//CV_BGR2HSV

	cvWaitKey(0);

	cvReleaseImage(&src);
	cvReleaseImage(&floathsv);
	cvReleaseImage(&floatimgH);
	cvReleaseImage(&floatimgS);
	cvReleaseImage(&floatimgV);

	return 0;
}
int main( )
{
	Mat src = imread("./data/pic001.png");
	//imshow("origin", src);
	
	//GaussianBlur(src, src, Size(3, 3), 0, 0);
	//src.convertTo(src, CV_32F, 1 / 255.0);

	Mat dst;
	cvtColor(src, dst, CV_RGB2HSV);
	vector<Mat> mv;
	split(dst,mv);
	imshow("RGB", dst);
	imshow("H", mv[0]);
	imshow("S", mv[1]);
	imshow("V", mv[2]);
	 
	//Mat dst;
	//GaussianBlur(src, dst, Size(3, 3), 0, 0);
	//imshow("Gaussian", dst);
	//imwrite("./data/Gaussian.jpg", dst);
	//cvtColor(src, dst, CV_BGR2HSV);
	waitKey();
	return 0;
}
