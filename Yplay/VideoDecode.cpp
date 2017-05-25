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
	update(); //调用update将执行 paintEvent函数
}

void VideoDecode::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, this->width(), this->height()); //先画成黑色

	if (m_image.size().width() <= 0) return;

	///将图像按比例缩放成和窗口一样大小
	QImage img = m_image.scaled(this->size(), Qt::KeepAspectRatio);

	int x = this->width() - img.width();
	int y = this->height() - img.height();

	x /= 2;
	y /= 2;

	painter.drawImage(QPoint(x, y), img); //画出图像
}



void VideoDecode::slotGetOneFrame(QImage img) {
	m_image = img;
	update(); //调用update将执行 paintEvent函数
}
