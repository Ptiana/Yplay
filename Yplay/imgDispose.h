#ifndef _IMGDISPOSE_H_
#define _IMGDISPOSE_H_
#include "publicHead.h"
#include "QImage"
using namespace std;
using namespace cv;
//�ж��Ƿ������Ļ
bool existFansub(Mat src);
//ͳ�ƶ�ֵ��ͼƬ��ÿ�е����������
bool countJumpPixel(Mat src, vector <int> &jumpArr);
//�ܾ������������ж��Ƿ������Ļ
bool jumpCharactJudge(vector <int> &jumpArr);
//��Ļ���ƱȽϣ��ж����Ʒ���true
bool similarCompare(Mat targetImg, Mat testImg);
// ��ȡ��֡ͼ��ָ���������ص���Сֵ
uchar getMinPixel(vector<Mat>src, int row, int col);
//��ͼ��Сֵ�ں��ں�
void minValueFuse(vector<Mat>src, Mat& dst);
//ͳ��ÿ��ֵΪ255�����ظ���----��ֱͶӰ
void verticalProjection(Mat src, vector<int>&colWhitePixel);
//ͳ��ÿ��ֵΪ255�����ظ���---------ˮƽͶӰ
void HorizontalProjection(Mat src, vector<int>&rowWhitePixel);
//Ѱ�ҽ����ŵİ�ɫ�����ڴ�ֱ����ͶӰ����Ϊ��ľ���
int findNextColZeo(int currentIndex, vector<int>colWhitePixel);
// ͼ���ʽת��
QImage MatToQImage(const cv::Mat& mat);
//ɾ���и�������ַ������¿հײ���
bool clearEmpty(Mat src, Mat &dst);
#endif//_IMGDISPOSE_H_
