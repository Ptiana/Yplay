#include "yplay.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Yplay w;
	w.show();
	return a.exec();
}
