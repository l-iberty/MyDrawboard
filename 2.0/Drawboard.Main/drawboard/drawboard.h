#ifndef DRAWBOARD_H
#define DRAWBOARD_H

#include <QtWidgets/QMainWindow>
#include "ui_drawboard.h"

class drawboard : public QMainWindow
{
	Q_OBJECT

public:
	drawboard(QWidget *parent = 0);
	~drawboard();

private:
	Ui::drawboardClass ui;
};

#endif // DRAWBOARD_H
