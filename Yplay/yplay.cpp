#include "yplay.h"
#include <QFileDialog>
#include <qwindow.h>
Yplay::Yplay(QWidget *parent)
	: QMainWindow(parent), m_trueFilePath(false)
{
	ui.setupUi(this);
	initFormat();
	qtaudioPlayer = new QMediaPlayer;
}

Yplay::~Yplay()
{

}

void Yplay::initFormat()
{
	//设置无边框
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
	//初始化事件过滤器
	enventProxy = new EnventProxy(this);
	enventProxy->SetBorderWidth(8, 8, 8, 8);
	//将窗口的子控件注册到事件过滤器
	registerEventFilter();


}

void Yplay::registerEventFilter()
{
	this->installEventFilter(enventProxy);
	ui.btn_exit->setMouseTracking(true);
	ui.btn_exit->installEventFilter(enventProxy);
	ui.btn_max->setMouseTracking(true);
	ui.btn_max->installEventFilter(enventProxy);
	ui.btn_min->setMouseTracking(true);
	ui.btn_min->installEventFilter(enventProxy);
}



void Yplay::btn_openFile_click()
{
	filePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开视频"), ".", tr("video Files(*.mp4 *.avi)"));
	if (filePath.length() != 0)
	{
		existVideo = true;
		videoDispose = new FansubTransalte();
		videoDispose->start();
		//m_trueFilePath = true;
	}
}



void Yplay::btn_playVideo_click()
{
	QTimer *timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(videoPlay()));

	timer->start(1000.0 /100);
	qtaudioPlayer->setMedia(QUrl::fromLocalFile(filePath));
	
}

void Yplay::videoPlay()
{
	Mat temp;
	//clock_t star, cur;
	//star = clock();
	static int index = 1;
	double base = 1000 / frameRate;
	static bool star=true;
	

		if (playFansubNum < dealFansubNum)
		{

			if (star)
			{
				qtaudioPlayer->play();
				star = false;
			}
			if ((base*index) < qtaudioPlayer->position())
			{
				temp = resultFrame.front();
				resultFrame.pop_front();
				cv::resize(temp, temp, Size(ui.lbl_play->width(), ui.lbl_play->height()), 0, 0, CV_INTER_LINEAR);
				ui.lbl_play->setPixmap(QPixmap::fromImage(MatToQImage(temp)));
				playFansubNum++;
				index++;
			}
		

			//	qtaudioPlayer->stop();
		}
	


}