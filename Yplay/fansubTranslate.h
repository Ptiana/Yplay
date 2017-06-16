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
	//打开视频文件并获取视频文件的帧时间戳和总帧数
	bool videoOpen(QString filePath, int &timeStamp, long &sumNum);
	void run();
	void stop();
	//处理字幕
	void fansubHandle();
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

    void scheduelChange(int value);//修改播放进度
private:
	//当前要处理的帧在视频所有帧中的索引
	int m_currentHandleIndex;
	volatile  bool end;
	//打开的视频
	VideoCapture newVideo;
	//要进行字幕融合处理的帧
	vector<Mat>fansubFuseFrame;
	//已经读入的帧
	vector<Mat>readFrame;
	//表示每次跳几帧选一帧处理
	int m_jumpFrameNum;
	//字幕最小值融合结果
	Mat minFuseResult;

	//用于存放翻译之后的字幕
	QString m_fansubText;
	//用于翻译处理的类
	Translate *m_tran;

};

#endif//_FANSUBTRANSLATE_H_
