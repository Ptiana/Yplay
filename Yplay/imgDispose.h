#ifndef _IMGDISPOSE_H_
#define _IMGDISPOSE_H_
#include "publicHead.h"
#include "QImage"
using namespace std;
using namespace cv;
//判断是否存在字幕
bool existFansub(Mat src);
//统计二值化图片中每行的跳变点数量
bool countJumpPixel(Mat src, vector <int> &jumpArr);
//很据跳变特征点判断是否存在字幕
bool jumpCharactJudge(vector <int> &jumpArr);
//字幕相似比较，判定相似返回true
bool similarCompare(Mat targetImg, Mat testImg);
// 获取多帧图像指定坐标像素的最小值
uchar getMinPixel(vector<Mat>src, int row, int col);
//多图最小值融合融合
void minValueFuse(vector<Mat>src, Mat& dst);
//统计每列值为255的像素个数----垂直投影
void verticalProjection(Mat src, vector<int>&colWhitePixel);
//统计每行值为255的像素个数---------水平投影
void HorizontalProjection(Mat src, vector<int>&rowWhitePixel);
//寻找紧接着的白色像素在垂直方向投影数量为零的距离
int findNextColZeo(int currentIndex, vector<int>colWhitePixel);
// 图像格式转换
QImage MatToQImage(const cv::Mat& mat);
//删掉切割出来的字符的上下空白部分
bool clearEmpty(Mat src, Mat &dst);
#endif//_IMGDISPOSE_H_
