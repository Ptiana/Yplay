#ifndef _SHARESPACE_H_
#define _SHARESPACE_H_
#include "publicHead.h"
#include "QMutex"

using namespace cv;
using namespace std;
//���ڹ��������resultFrame
QMutex g_mutex;
//���������Ƶ֡��ŵ�����
list<Mat>g_resultFrame;



//������ƫ��ԭ�������Ҳ������Ϊ�޸��˽���
bool progressBarVary = false;


#endif//_SHARESPACE_H_
