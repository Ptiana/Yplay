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

using namespace std;
using namespace cv;

extern QString filePath;
extern bool existVideo;
// �Ѿ��������Ļ����
extern int dealFansubNum;
//�Ѿ����Ź�����Ļ����
extern int playFansubNum;
//���������Ƶ֡��ŵ�����
extern list<Mat>resultFrame;

extern int frameRate;


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
	FansubTransalte *videoDispose;
	QMediaPlayer *qtaudioPlayer;
	EnventProxy *enventProxy;
signals:
	void sig_GetOneFrame(QImage); //û��ȡ��һ֡ͼ�� �ͷ��ʹ��ź�
private slots:
	//����Ƶ�ļ�
	void btn_openFile_click();
	void btn_playVideo_click();
	void videoPlay();
private:
	QString m_filePath;
	bool m_trueFilePath;
};

#endif // YPLAY_H
