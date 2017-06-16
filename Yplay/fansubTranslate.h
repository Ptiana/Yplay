#ifndef _FANSUBTRANSLATE_H_
#define _FANSUBTRANSLATE_H_
#include "publicHead.h"
#include "imgDispose.h"
#include"knn.h"
#include "translate.h"
#include "CvxText.h"
#include <QThread>
using namespace std;
using namespace cv;
extern bool progressBarVary;

extern QMutex g_mutex;
extern list<Mat>g_resultFrame;



class FansubTransalte:public QThread
{
	Q_OBJECT
public:
	FansubTransalte();
	~FansubTransalte();
	//����Ƶ�ļ�����ȡ��Ƶ�ļ���֡ʱ�������֡��
	bool videoOpen(QString filePath, int &timeStamp, long &sumNum);
	void run();
	void stop();
	//������Ļ
	void fansubHandle();
	//��Ļ׷��
	bool  FansubTrack();
	//������������jumpFrameNum֡ȡ��4֡
	bool getNextfarme(Mat& src_frame);
	//��Ļ�и�
	void fansubCut();
	//��Ļ�зָ��һ��ͼƬ����ɨ�裬������һ�����������Ļ��ʼλ��
	void fansubRowCut(Mat src, vector<vector<int>>&rowStaAndEnd);
	// ��Ļ�зָ� �������ͼƬ�ϵ����ݽ������и�
	void fansubColCut(Mat src, vector<int>&colStaAndEnd);
	//�ַ��и���ʶ��
	void charCutDistinguish(Mat src, QString& strText);
	
	//����Ͷ��
	void loadTranslation(int star, int end, QString txt);
	//������õ�����д�빲���ڴ�
	void writeToShareSpace(vector<Mat>src);

    void scheduelChange(int value);//�޸Ĳ��Ž���
private:
	//��ǰҪ�����֡����Ƶ����֡�е�����
	int m_currentHandleIndex;
	volatile  bool end;
	//�򿪵���Ƶ
	VideoCapture newVideo;
	//Ҫ������Ļ�ںϴ����֡
	vector<Mat>fansubFuseFrame;
	//�Ѿ������֡
	vector<Mat>readFrame;
	//��ʾÿ������֡ѡһ֡����
	int m_jumpFrameNum;
	//��Ļ��Сֵ�ںϽ��
	Mat minFuseResult;

	//���ڴ�ŷ���֮�����Ļ
	QString m_fansubText;
	//���ڷ��봦�����
	Translate *m_tran;

};

#endif//_FANSUBTRANSLATE_H_
