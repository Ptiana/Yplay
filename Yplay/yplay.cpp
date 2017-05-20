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
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
	enventProxy = new EnventProxy(this);
	enventProxy->SetBorderWidth(8, 8, 8, 8);
}


