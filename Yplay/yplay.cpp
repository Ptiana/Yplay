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
	ui.btn_exit->setMouseTracking(true);
	ui.btn_exit->installEventFilter(enventProxy);
	ui.btn_max->setMouseTracking(true);
	ui.btn_max->installEventFilter(enventProxy);
	ui.btn_min->setMouseTracking(true);
	ui.btn_min->installEventFilter(enventProxy);
}


void Yplay::btn_openFile_click()
{
	m_filePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("����Ƶ"), ".", tr("video Files(*.mp4 *.avi)"));
	if (m_filePath.length() != 0)
		m_trueFilePath = true;
}