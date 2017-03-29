#include <iostream>
#include <highgui/highgui.hpp>


void onMouse(int event, int x, int y, int flags, void* param);  //判断鼠标动作
int grabcut();  //GrabCut算法，提取前景