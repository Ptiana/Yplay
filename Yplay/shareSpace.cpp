#ifndef _SHARESPACE_H_
#define _SHARESPACE_H_
#include "publicHead.h"

using namespace cv;
using namespace std;

//已经处理的字幕条数
int dealFansubNum=0;
//已经播放过的字幕条数
int playFansubNum = 0;
//处理完的视频帧存放的容器
list<Mat>resultFrame;
//打开的视频文件路径
QString filePath="";
//是否已经打开视频文件
bool existVideo =false;
//当前要处理的帧在视频所有帧中的索引
int currentHandleIndex=0;
//进度条偏离原来轨道，也就是认为修改了进度
bool progressBarVary = false;
int frameRate = 0;


#endif//_SHARESPACE_H_
