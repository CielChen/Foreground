/*
------------------------------------------------
Author: CIEL
Date: 2017/02/16
Function: 提取图片前景
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

	//法1：GrabCut算法
//	grabcut();

	//法2：差分法，得到前景灰度图
//	differ();

	//法3：差分法，得到前景RGB图
	differRGB();


	return 0;
}
