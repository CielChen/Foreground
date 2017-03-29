/*
------------------------------------------------
Author: CIEL
Date: 2017/02/17
Function: ��ַ�����ȡͼƬǰ�����õ���ǰ��ͼƬ�ǻҶ�ͼ
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

	//���뱳��ͼ��
	background=cvLoadImage("F:\\Code\\Foreground\\Data\\Background\\20170228111043_back.jpg");
	cvNamedWindow("����ͼ��",0);
	cvResizeWindow("����ͼ��", 1216, 684);  //�Դ��ڽ��д�С���¶���
	cvShowImage("����ͼ��",background);

	//���볡��ͼ��
	scene=cvLoadImage("F:\\Code\\Foreground\\Data\\Scene\\20170228111043_scene.jpg");
	cvNamedWindow("����ͼ��",WINDOW_NORMAL);
	cvResizeWindow("����ͼ��", 1216, 684);  //�Դ��ڽ��д�С���¶���
	cvShowImage("����ͼ��",scene);

	backgroundImg=cvCreateImage(cvSize(background->width, background->height),IPL_DEPTH_8U,1);
	sceneImg=cvCreateImage(cvSize(scene->width, scene->height),IPL_DEPTH_8U,1);
	foregoundImg=cvCreateImage(cvSize(scene->width, scene->height),IPL_DEPTH_8U,1);

	backgroundMat=cvCreateMat(background->height, background->width, CV_32FC1);
	sceneMat=cvCreateMat(background->height, background->width, CV_32FC1);
	foregroundMat=cvCreateMat(background->height, background->width, CV_32FC1);

	//��ͼ��ת���ɵ�ͨ��ͼ�񣬼��Ҷ�ͼ
	cvCvtColor(background, backgroundImg, CV_BGR2GRAY);
	cvCvtColor(scene, sceneImg, CV_BGR2GRAY);

	//cvConvert(src,dst)����ͼ���������������֮���ת��������ͼ�����������ֵ�����󣬻�Ѿ����ֵת��Ϊͼ������ݲ���
	cvConvert(backgroundImg, backgroundMat);
	cvConvert(sceneImg, sceneMat);
	cvConvert(foregoundImg, foregroundMat);

	//��˹�˲���ƽ��ͼ��
	cvSmooth(sceneMat, sceneMat, CV_GAUSSIAN, 3, 0, 0);

	//��֣�����ͼ��-����ͼ��
	cvAbsDiff(sceneMat, backgroundMat, foregroundMat);

	//��ǰ��ת��Ϊͼ���ʽ��������ʾ.ע����ʱ�õ���ǰ���ǻҶ�ͼ
	cvConvert(foregroundMat, foregoundImg);

	cvNamedWindow("ǰ��ͼ��",WINDOW_NORMAL);
	cvResizeWindow("ǰ��ͼ��", 1216, 684);  //�Դ��ڽ��д�С���¶���
	cvShowImage("ǰ��ͼ��", foregoundImg);
	cvSaveImage("F:\\Code\\Foreground\\Data\\Differ\\Foreground\\20170228111043_fore.jpg", foregoundImg);  //����ǰ��ͼƬ

	//���ǰ���Ҷ�ͼ������
/*	int width=foregoundImg->width;   //ǰ�����
	int height=foregoundImg->height;  //ǰ���߶�
	for(size_t row=0; row<height; row++)
	{
		uchar* ptr=(uchar*)foregoundImg->imageData + row*foregoundImg->width;   //��ûҶ�ֵ����ָ��
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
	cvDestroyWindow("����ͼ��");
	cvDestroyWindow("����ͼ��");
	cvDestroyWindow("ǰ��ͼ��");
		
	return 0;
}