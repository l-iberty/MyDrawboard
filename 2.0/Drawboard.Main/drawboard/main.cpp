#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow win;
	win.setWindowIcon(QIcon(":/drawboard/Resources/appicon.png"));
	win.show();
	return app.exec();
}
