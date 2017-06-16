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

//���������Ƶ֡��ŵ�����
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
	//����Ƶ�ļ�
	void btn_openFile_click();
	void btn_play_click();
	void btn_volum_click();
	void bar_schedule_realse();
	void bar_schedule_move(int);
	void bar_schedule_press();

	void videoPlay();
	void volum_change(int value);
private:
	
	bool m_bAduioStar;	   //�����ж���Ƶ�Ƿ��Ѿ���ʼ����
	bool m_bPause;         //��ͣ
	bool m_bMute;          //��ǰ�Ƿ��ھ���״̬
	bool m_bSchePress;     //�Ƿ��½�����
	int  m_scheMoveValue;  //��¼��ǰ�������϶���λ��
	int m_frameTimeStamp;  
	volatile long m_scheIndex; //��ǰ����֡����
	QTimer *m_timer;
};

#endif // YPLAY_H
