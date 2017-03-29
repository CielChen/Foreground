/*
------------------------------------------------
Author: CIEL
Date: 2017/02/17
Function: 差分法，提取图片前景，得到的前景图片是灰度图
------------------------------------------------
*/

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <Windows.h>
#include "differ.h"

using namespace cv;
using namespace std;

int differ()
{
	IplImage* background;
	IplImage* scene;
	IplImage* backgroundImg=NULL;
	IplImage* sceneImg=NULL;
	IplImage* foregoundImg=NULL;


	CvMat* backgroundMat=NULL;
	CvMat* sceneMat=NULL;
	CvMat* foregroundMat=NULL;

	//载入背景图像
	background=cvLoadImage("F:\\Code\\Foreground\\Data\\Background\\20170228111043_back.jpg");
	cvNamedWindow("背景图像",0);
	cvResizeWindow("背景图像", 1216, 684);  //对窗口进行大小重新定义
	cvShowImage("背景图像",background);

	//载入场景图像
	scene=cvLoadImage("F:\\Code\\Foreground\\Data\\Scene\\20170228111043_scene.jpg");
	cvNamedWindow("场景图像",WINDOW_NORMAL);
	cvResizeWindow("场景图像", 1216, 684);  //对窗口进行大小重新定义
	cvShowImage("场景图像",scene);

	backgroundImg=cvCreateImage(cvSize(background->width, background->height),IPL_DEPTH_8U,1);
	sceneImg=cvCreateImage(cvSize(scene->width, scene->height),IPL_DEPTH_8U,1);
	foregoundImg=cvCreateImage(cvSize(scene->width, scene->height),IPL_DEPTH_8U,1);

	backgroundMat=cvCreateMat(background->height, background->width, CV_32FC1);
	sceneMat=cvCreateMat(background->height, background->width, CV_32FC1);
	foregroundMat=cvCreateMat(background->height, background->width, CV_32FC1);

	//将图像转换成单通道图像，即灰度图
	cvCvtColor(background, backgroundImg, CV_BGR2GRAY);
	cvCvtColor(scene, sceneImg, CV_BGR2GRAY);

	//cvConvert(src,dst)用于图像数据类型与矩阵之间的转换，并把图像的数据区赋值给矩阵，或把矩阵的值转换为图像的数据部分
	cvConvert(backgroundImg, backgroundMat);
	cvConvert(sceneImg, sceneMat);
	cvConvert(foregoundImg, foregroundMat);

	//高斯滤波，平滑图像
	cvSmooth(sceneMat, sceneMat, CV_GAUSSIAN, 3, 0, 0);

	//差分：场景图像-背景图像
	cvAbsDiff(sceneMat, backgroundMat, foregroundMat);

	//将前景转化为图像格式，用以显示.注：此时得到的前景是灰度图
	cvConvert(foregroundMat, foregoundImg);

	cvNamedWindow("前景图像",WINDOW_NORMAL);
	cvResizeWindow("前景图像", 1216, 684);  //对窗口进行大小重新定义
	cvShowImage("前景图像", foregoundImg);
	cvSaveImage("F:\\Code\\Foreground\\Data\\Differ\\Foreground\\20170228111043_fore.jpg", foregoundImg);  //保存前景图片

	//输出前景灰度图的像素
/*	int width=foregoundImg->width;   //前景宽度
	int height=foregoundImg->height;  //前景高度
	for(size_t row=0; row<height; row++)
	{
		uchar* ptr=(uchar*)foregoundImg->imageData + row*foregoundImg->width;   //获得灰度值数据指针
		for(size_t col=0; col<width; col++)
		{
			int intensity=ptr[col];
			cout<<intensity<<" ";
		}
		cout<<endl;
	}
*/
	cvReleaseImage(&scene);
	cvReleaseImage(&background);
	cvReleaseImage(&backgroundImg);
	cvReleaseImage(&sceneImg);
	cvReleaseImage(&foregoundImg);
	cvReleaseMat(&backgroundMat);
	cvReleaseMat(&sceneMat);
	cvReleaseMat(&foregroundMat);

	cvWaitKey(0);
	cvDestroyWindow("场景图像");
	cvDestroyWindow("背景图像");
	cvDestroyWindow("前景图像");
		
	return 0;
}