#ifndef YPLAY_H
#define YPLAY_H

#include <QtWidgets/QMainWindow>
#include "ui_yplay.h"
#include "eventProxy.h"
#include "fansubTranslate.h"



#include <QtWidgets/QMainWindow>

#include "publicHead.h"
#include "imgDispose.h"
#include <QFileDialog>
#include "fansubTranslate.h"
#include<QMediaPlayer>
#include "QMutex"

using namespace std;
using namespace cv;

extern QMutex g_mutex;

//处理完的视频帧存放的容器
extern list<Mat>g_resultFrame;



class EnventProxy;
class Yplay : public QMainWindow
{
	Q_OBJECT

public:
	explicit Yplay(QWidget *parent = 0);
	~Yplay();
	void initFormat();
	void registerEventFilter();


private:
	Ui::YplayClass ui;
	FansubTransalte *m_videoDispose;
	QMediaPlayer *m_audioPlayer;
	EnventProxy *m_enventProxy;
private slots:
	//打开视频文件
	void btn_openFile_click();
	void btn_play_click();
	void btn_volum_click();
	void bar_schedule_realse();
	void bar_schedule_move(int);
	void bar_schedule_press();

	void videoPlay();
	void volum_change(int value);
private:
	
	bool m_bAduioStar;	   //用于判断音频是否已经开始播放
	bool m_bPause;         //暂停
	bool m_bMute;          //当前是否处于静音状态
	bool m_bSchePress;     //是否按下进度条
	int  m_scheMoveValue;  //记录当前进度条拖动的位置
	int m_frameTimeStamp;  
	volatile long m_scheIndex; //当前播放帧索引
	QTimer *m_timer;
};

#endif // YPLAY_H
