#ifndef _VIDEODECODE_H_
#define _VIDEODECODE_H_
#include <QOpenGLWidget>
#include <QPainter>
class VideoDecode :
	public QWidget
{
	Q_OBJECT

public:
	explicit VideoDecode(QWidget *parent = 0);
	~VideoDecode();

	void setFileName(QString path);

	void drawImage(QImage);

protected:
	
	void paintEvent(QPaintEvent *event);
	public slots :
	void slotGetOneFrame(QImage);


private:
	QString mFileName;
	QImage m_image;

};

#endif//_VIDEODECODE_H_
