#ifndef _SHARESPACE_H_
#define _SHARESPACE_H_
#include "publicHead.h"
#include "QMutex"

using namespace cv;
using namespace std;
//用于管理互斥访问resultFrame
QMutex g_mutex;
//处理完的视频帧存放的容器
list<Mat>g_resultFrame;



//进度条偏离原来轨道，也就是认为修改了进度
bool progressBarVary = false;


#endif//_SHARESPACE_H_
