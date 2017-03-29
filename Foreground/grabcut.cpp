/*
------------------------------------------------
Author: CIEL
Date: 2017/02/16
Function: GrabCut�㷨����ȡͼƬǰ��
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
#include "grabcut.h"

using namespace cv;
using namespace std;
Rect selection;
Mat img,img0;
Point prePt(-1,-1);  //��ά��(-1,-1)

//�ж���궯��
void onMouse(int event, int x, int y, int flags, void* param)
{
	if(event == CV_EVENT_LBUTTONDOWN){  //CV_EVENT_LBUTTONDOWN ������
		prePt=Point(x,y);
	}
	else if(event == CV_EVENT_MOUSEMOVE && (flags && CV_EVENT_FLAG_LBUTTON)){  //CV_EVENT_MOUSEMOVE ������CV_EVENT_FLAG_LBUTTON �����ק
		img=img0.clone();
		
		//rectangle()���������Ρ�ͼ�񱻻���img�ϣ����������ԽǶ��㣬������ɫ�����ο�Ĵ�ϸ
		//Rect�������������Ͻǵ����ꡢ����
		//Scalar(0, 0, 255):��ʾRGB��ɫ��R=255��G=0��B=0
		rectangle(img, Rect(prePt.x, prePt.y, abs(x-prePt.x), abs(y-prePt.y) ), Scalar(0, 0, 255), 3);

		selection=Rect(prePt.x, prePt.y, abs(x-prePt.x), abs(y-prePt.y) );
	}
	else if(event == CV_EVENT_LBUTTONUP || !(flags && CV_EVENT_FLAG_LBUTTON) ){  //CV_EVENT_LBUTTONUP����ſ�
		prePt=Point(-1,-1);
	}
	imshow("ԭͼ", img);
}

int grabcut()
{
	//���볡��ͼƬ
	img=imread("F:\\Code\\Foreground\\Data\\GrabCut\\origin\\20170228111043_scene.jpg",1);
	
	img0=img.clone();
	namedWindow("ԭͼ", WINDOW_AUTOSIZE);
	imshow("ԭͼ",img);

	/*setMouseCallback()
	��һ����������������
	�ڶ��������������Ӧ�������ص�������ָ��������ÿ�����ʱ�䷢�͵�ʱ�򣬱����õĺ���ָ�롣*/
	setMouseCallback("ԭͼ", onMouse);
	
	Mat result;  //4�ֿ��ܽ��
	Mat bgModel, fgModel;  //������ǰ��
	cout<<"--------GrabCut�㷨----------"<<endl;
	cout<<"---------���ֶ�ѡ��ǰ����ѡ�ú�p���˳��밴q-----"<<endl;
	for(;;){
		int c=waitKey(10);
		if((char)c == 'p'){
			/*grabCut()
			��һ������������ͼ�����ͱ���ΪCV_8UC3
			�ڶ�������mask���ֶν������Сͬ��һ������������ʽΪCV_8UC1��ֻ���ǵ�ͨ���ġ�
			��4�ֿ��ܽ����������ǰ�������ܱ���������ǰ��
			����������������ǰ���ľ���
			���ĸ��������������ǰ��������
			������������������������������Խ�࣬Ч��Խ�ã���ʱ��ҲԽ��
			���߸��������þ���
			*/
			cout<<"���ڴ���ͼ�񡤡���"<<endl;
			grabCut(img0, result, selection, bgModel, fgModel, 5, GC_INIT_WITH_RECT);
			compare(result, GC_PR_FGD, result, CMP_EQ);  //�õ�ǰ��mask��GC_PR_FGDǰ����CMP_EQ�Ƚ����������Ƿ����

			Mat foregound(img.size(), CV_8UC3, Scalar::all(255));
			img0.copyTo(foregound, result);
			namedWindow("GrabCut", WINDOW_AUTOSIZE);
			imshow("GrabCut",foregound);
			//����ǰ��ͼ
			imwrite("F:\\Code\\Foreground\\Data\\GrabCut\\foreground\\20170228111043_fore.jpg",foregound);
		}
		if(char(c)=='q')
			return 0;
	}
	return 0;
}
