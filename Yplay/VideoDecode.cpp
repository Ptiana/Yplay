#include "VideoDecode.h"



VideoDecode::VideoDecode(QWidget *parent)
{
	
}


VideoDecode::~VideoDecode()
{
}

void VideoDecode::setFileName(QString path)
{ 
	mFileName = path;
}

void VideoDecode::drawImage(QImage mImage)
{
	m_image = mImage;
	update(); //����update��ִ�� paintEvent����
}

void VideoDecode::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, this->width(), this->height()); //�Ȼ��ɺ�ɫ

	if (m_image.size().width() <= 0) return;

	///��ͼ�񰴱������ųɺʹ���һ����С
	QImage img = m_image.scaled(this->size(), Qt::KeepAspectRatio);

	int x = this->width() - img.width();
	int y = this->height() - img.height();

	x /= 2;
	y /= 2;

	painter.drawImage(QPoint(x, y), img); //����ͼ��
}



void VideoDecode::slotGetOneFrame(QImage img) {
	m_image = img;
	update(); //����update��ִ�� paintEvent����
}
