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
	//处理字幕
	void fansubHandle(int starFrame);
	//字幕追踪
	bool  FansubTrack();
	//跳过接下来的jumpFrameNum帧取第4帧
	bool getNextfarme(Mat& src_frame);
	//字幕切割
	void fansubCut();
	//字幕行分割对一张图片进行扫描，并返回一条或多条的字幕起始位置
	void fansubRowCut(Mat src, vector<vector<int>>&rowStaAndEnd);
	// 字幕列分割 对输入的图片上的内容进行列切割
	void fansubColCut(Mat src, vector<int>&colStaAndEnd);
	//字符切割与识别
	void charCutDistinguish(Mat src, QString& strText);
	
	//译文投屏
	void loadTranslation(int star, int end, QString txt);
	//将处理好的数据写入共享内存
	void writeToShareSpace(vector<Mat>src);
private slots:
	//检查是否已经成功打开了视频文件
	bool videoHandleCheck();
private:
	bool end;
	//打开的视频
	VideoCapture newVideo;

	//要进行字幕融合处理的帧
	vector<Mat>fansubFuseFrame;
	//已经读入的帧
	vector<Mat>readFrame;
	//表示每次跳几帧选一帧处理
	int jumpFrameNum;
	//字幕最小值融合结果
	Mat minFuseResult;

	QString fansubText;
	//翻译处理的类
	Translate *tran;

};

#endif//_FANSUBTRANSLATE_H_
