#include "yplay.h"

Yplay::Yplay(QWidget *parent)
	: QMainWindow(parent)
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
	ui.btn_exit->installEventFilter(enventProxy);
	ui.btn_max->installEventFilter(enventProxy);
	ui.btn_min->setMouseTracking(true);
	ui.btn_min->installEventFilter(enventProxy);
}


