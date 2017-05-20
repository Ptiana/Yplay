#ifndef YPLAY_H
#define YPLAY_H

#include <QtWidgets/QMainWindow>
#include "ui_yplay.h"
#include "eventProxy.h"
class EnventProxy;
class Yplay : public QMainWindow
{
	Q_OBJECT

public:
	explicit Yplay(QWidget *parent = 0);
	~Yplay();
	void initFormat();
	void registerEventFilter();


private:
	EnventProxy *enventProxy;
	Ui::YplayClass ui;
};

#endif // YPLAY_H
