#include "yplay.h"
#include <QFileDialog>
Yplay::Yplay(QWidget *parent)
	: QMainWindow(parent), m_trueFilePath(false)
{
	ui.setupUi(this);
	initFormat();

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
	m_filePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开视频"), ".", tr("video Files(*.mp4 *.avi)"));
	if (m_filePath.length() != 0)
		m_trueFilePath = true;
}