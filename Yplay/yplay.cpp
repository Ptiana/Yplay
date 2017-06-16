#include "yplay.h"
#include <QFileDialog>
#include <qwindow.h>
Yplay::Yplay(QWidget *parent)
	: QMainWindow(parent)
{
	//UI关联
	ui.setupUi(this);
	//初始化变量
	m_scheMoveValue = 0;
	m_bAduioStar = false;
	m_bPause = true;
	m_bMute = false;
	m_bSchePress = false;
	m_scheIndex = 1;
	m_audioPlayer = new QMediaPlayer;
	m_videoDispose = new FansubTransalte;
	m_timer = new QTimer();
	//初始化界面
	initFormat();
	//关联信号与槽
	connect(m_timer, SIGNAL(timeout()), this, SLOT(videoPlay()));
	connect(ui.bar_schedule, SIGNAL(sliderReleased()), this, SLOT(bar_schedule_realse()));
	connect(ui.bar_schedule, SIGNAL(sliderPressed()), this, SLOT(bar_schedule_press()));
	connect(ui.bar_schedule, SIGNAL(sliderMoved(int)), this, SLOT(bar_schedule_move(int)));



}

Yplay::~Yplay()
{
	delete m_audioPlayer;
	delete m_timer;
	
	delete m_enventProxy;
	if (!m_videoDispose)
	delete m_videoDispose;
}

void Yplay::initFormat()
{
	//设置无边框
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
	//设置音量条的范围
	ui.bar_volume->setRange(0,100);
	ui.bar_volume->setValue(30);
	//初始化事件过滤器
	m_enventProxy = new EnventProxy(this);
	m_enventProxy->SetBorderWidth(8, 8, 8, 8);
	//将窗口的子控件注册到事件过滤器
	registerEventFilter();

}

void Yplay::registerEventFilter()
{
	this->installEventFilter(m_enventProxy);
	ui.btn_exit->setMouseTracking(true);
	ui.btn_exit->installEventFilter(m_enventProxy);
	ui.btn_max->setMouseTracking(true);
	ui.btn_max->installEventFilter(m_enventProxy);
	ui.btn_min->setMouseTracking(true);
	ui.btn_min->installEventFilter(m_enventProxy);
}



void Yplay::btn_openFile_click()
{
	QString filePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开视频"), ".", tr("video Files(*.mp4 *.avi)"));
	if (filePath.length() != 0)
	{
		long scheduleRange = 0;
		//打开文件并获取视频信息
		if (m_videoDispose->videoOpen(filePath,m_frameTimeStamp, scheduleRange))
		{
			//设置进度条范围
			ui.bar_schedule->setRange(0, scheduleRange-1);
			m_videoDispose->start();
			m_timer->start(20);
			m_bPause = false;
			m_audioPlayer->setMedia(QUrl::fromLocalFile(filePath));

		}
		//m_trueFilePath = true;
	}
}
  


void Yplay::btn_play_click()
{
	
	m_bPause = !m_bPause;
	if (m_bPause)
	{
		m_audioPlayer->pause();
	}
	else
	{
		m_audioPlayer->play();

	}
}

void Yplay::btn_volum_click()
{
	m_bMute = !m_bMute;
	if (m_bMute)
	{
		ui.btn_volume->setStyleSheet("\
                         QPushButton{\
		                 image:url(:/Resources/png/volum_min.png);\
		                 color:white;\
						 border-radius:10px;\
						 border:2px groove gray;\
						 border-style:outset;\
							}\
						 QPushButton:hover{\
							background-color:white;\
							color:black;\
							}\
							QPushButton:pressed{\
							border-style:inset;\
								} ");  
		m_audioPlayer->setVolume(0);
	}
	else
	{
		ui.btn_volume->setStyleSheet("\
                         QPushButton{\
		                 image:url(:/Resources/png/volum_midel.png);\
		                 color:white;\
						 border-radius:10px;\
						 border:2px groove gray;\
						 border-style:outset;\
							}\
						 QPushButton:hover{\
							background-color:white;\
							color:black;\
							}\
							QPushButton:pressed{\
							border-style:inset;\
								} ");
		m_audioPlayer->setVolume(ui.bar_volume->value());

	}
}

void Yplay::bar_schedule_press()
{
	m_bSchePress = true;

}

void Yplay::bar_schedule_move(int value)
{
	m_scheMoveValue = value;
}

void Yplay::bar_schedule_realse()
{
	//先把播放的停止防止数据停止获取后还在播放
	m_timer->stop();

	m_audioPlayer->pause();
	//获取当前调到的位置
	
	//停止采集数据
	m_videoDispose->stop();
	m_videoDispose->wait();
	//进度条重新标记进度
	m_bSchePress = false;
	//在新的位置上重新开始采集数据
	m_scheIndex = m_scheMoveValue +1;
	m_audioPlayer->setPosition(m_frameTimeStamp*m_scheMoveValue);
	m_videoDispose->scheduelChange(m_scheMoveValue);
	m_videoDispose->start();
	m_timer->start(10);
	m_bPause = false;
	m_bAduioStar = false;

}




void Yplay::videoPlay()
{
	Mat temp;


	if (!g_resultFrame.empty()&&!m_bPause)
	{
	
		//必须等到存在可以播放的视频时才能开始播放音频
		if (!m_bAduioStar)
		{
			m_audioPlayer->play();
			m_bAduioStar = true;
		}
		if ((m_frameTimeStamp*m_scheIndex)<(m_audioPlayer->position()))
		{
			temp = g_resultFrame.front();
			if (temp.empty())
				return;
			g_resultFrame.pop_front();
			cv::resize(temp, temp, Size(ui.lbl_play->width(), ui.lbl_play->height()), 0, 0, CV_INTER_LINEAR);
			ui.lbl_play->setPixmap(QPixmap::fromImage(MatToQImage(temp)));
			m_scheIndex++;
			if (!m_bSchePress)
				ui.bar_schedule->setSliderPosition(m_scheIndex);
		}
	}
	


}


void Yplay::volum_change(int value)
{
	if (!m_bMute)
		m_audioPlayer->setVolume(value);
}
