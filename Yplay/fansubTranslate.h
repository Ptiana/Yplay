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
extern bool existVideo;
extern QString filePath;
extern int currentHandleIndex;
extern bool progressBarVary;
extern list<Mat>resultFrame;
extern int dealFansubNum;
extern int frameRate;
class FansubTransalte:public QThread
{
	Q_OBJECT
public:
	FansubTransalte();
	~FansubTransalte();
	void run();
	//������Ļ
	void fansubHandle(int starFrame);
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
private slots:
	//����Ƿ��Ѿ��ɹ�������Ƶ�ļ�
	bool videoHandleCheck();
private:
	bool end;
	//�򿪵���Ƶ
	VideoCapture newVideo;

	//Ҫ������Ļ�ںϴ����֡
	vector<Mat>fansubFuseFrame;
	//�Ѿ������֡
	vector<Mat>readFrame;
	//��ʾÿ������֡ѡһ֡����
	int jumpFrameNum;
	//��Ļ��Сֵ�ںϽ��
	Mat minFuseResult;

	QString fansubText;
	//���봦�����
	Translate *tran;

};

#endif//_FANSUBTRANSLATE_H_
