/*
------------------------------------------------
Author: CIEL
Date: 2017/02/16
Function: ��ȡͼƬǰ��
------------------------------------------------
*/

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include "grabcut.h"
#include "differ.h"
#include "differRGB.h"

using namespace cv;
using namespace std;

int main()
{

	//��1��GrabCut�㷨
//	grabcut();

	//��2����ַ����õ�ǰ���Ҷ�ͼ
//	differ();

	//��3����ַ����õ�ǰ��RGBͼ
	differRGB();


	return 0;
}
