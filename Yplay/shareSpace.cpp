#ifndef _SHARESPACE_H_
#define _SHARESPACE_H_
#include "publicHead.h"

using namespace cv;
using namespace std;

//�Ѿ��������Ļ����
int dealFansubNum=0;
//�Ѿ����Ź�����Ļ����
int playFansubNum = 0;
//���������Ƶ֡��ŵ�����
list<Mat>resultFrame;
//�򿪵���Ƶ�ļ�·��
QString filePath="";
//�Ƿ��Ѿ�����Ƶ�ļ�
bool existVideo =false;
//��ǰҪ�����֡����Ƶ����֡�е�����
int currentHandleIndex=0;
//������ƫ��ԭ�������Ҳ������Ϊ�޸��˽���
bool progressBarVary = false;
int frameRate = 0;


#endif//_SHARESPACE_H_
