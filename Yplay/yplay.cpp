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
	//�����ޱ߿�
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
	//��ʼ���¼�������
	enventProxy = new EnventProxy(this);
	enventProxy->SetBorderWidth(8, 8, 8, 8);
	//�����ڵ��ӿؼ�ע�ᵽ�¼�������
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


