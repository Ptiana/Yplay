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
	void SetBorderWidth(int top, int right, int bottom, int left); // 设置四周边框宽度
	~EnventProxy();

protected:
	//九个区域的枚举值
	enum WidgetRegion {Top = 0, TopRight, Right, RightBottom, Bottom, LeftBottom, Left, LeftTop, Inner,Unknown};

protected:
	virtual bool eventFilter(QObject* obj, QEvent* event);  //事件筛选
	bool windFilter(QObject* obj, QEvent* event);           //代理窗体事件
	bool minFilter(QObject* obj, QEvent* event);            //最小化按钮事件
	void MakeRegions();                                     //算出当前窗体九宫格每个格子的rect
	WidgetRegion HitTest(const QPoint& pos);                //计算当前焦点在哪个区域
	void UpdateGeometry(int x, int y, int w, int h);        //更新主窗体位置
	void StartCursorTimer();                                //停止监控鼠标->变化样式
	void StopCursorTimer();                                 //停止监控鼠标->变化样式

private:
	QWidget* m_proxyWidget;		                             // 代理的窗体
	int m_top, m_right, m_bottom, m_left;	                 // 四周宽度
	QRect m_regions[9];		                                 // 九宫格，对应9个区域
	QPoint m_originPosGlobal;	                             // 拖拽前鼠标位置
	QRect m_originGeo;			                             // 拖拽前窗体位置和大小
	bool m_mousePressed;	                               	// 鼠标是否按下
	WidgetRegion m_regionPressed;	                        // 记录鼠标按下时所点击的区域
	int m_cursorTimerId;

};

#endif // DRAGPROXY_H
