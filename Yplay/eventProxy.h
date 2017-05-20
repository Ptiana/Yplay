#ifndef DRAGPROXY_H
#define DRAGPROXY_H

#include <QObject>
#include <QWidget>
#include <QEvent>
#include <QRect>
#include <QPoint>
#include "ui_yplay.h"

class EnventProxy : public QObject
{
	Q_OBJECT

public:
	EnventProxy(QWidget *parent);
	void SetBorderWidth(int top, int right, int bottom, int left); // �������ܱ߿���
	~EnventProxy();

protected:
	//�Ÿ������ö��ֵ
	enum WidgetRegion {Top = 0, TopRight, Right, RightBottom, Bottom, LeftBottom, Left, LeftTop, Inner,Unknown};

protected:
	virtual bool eventFilter(QObject* obj, QEvent* event);  //�¼�ɸѡ
	bool windFilter(QObject* obj, QEvent* event);           //�������¼�
	bool minFilter(QObject* obj, QEvent* event);            //��С����ť�¼�
	void MakeRegions();                                     //�����ǰ����Ź���ÿ�����ӵ�rect
	WidgetRegion HitTest(const QPoint& pos);                //���㵱ǰ�������ĸ�����
	void UpdateGeometry(int x, int y, int w, int h);        //����������λ��
	void StartCursorTimer();                                //ֹͣ������->�仯��ʽ
	void StopCursorTimer();                                 //ֹͣ������->�仯��ʽ

private:
	QWidget* m_proxyWidget;		                             // ����Ĵ���
	int m_top, m_right, m_bottom, m_left;	                 // ���ܿ��
	QRect m_regions[9];		                                 // �Ź��񣬶�Ӧ9������
	QPoint m_originPosGlobal;	                             // ��קǰ���λ��
	QRect m_originGeo;			                             // ��קǰ����λ�úʹ�С
	bool m_mousePressed;	                               	// ����Ƿ���
	WidgetRegion m_regionPressed;	                        // ��¼��갴��ʱ�����������
	int m_cursorTimerId;

};

#endif // DRAGPROXY_H
