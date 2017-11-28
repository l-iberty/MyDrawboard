#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets\qmainwindow.h>
#include <QtGui\qevent.h>
#include <QtWidgets\qaction.h>
#include <QtWidgets\qmenu.h>
#include <QtWidgets\qmenubar.h>
#include "shape.h"
#include "shapefactory.h"
#include "menuactionfactory.h"
#include "painter.h"
#include "painterfactory.h"
#include "file.h"

class Shape;

class MainWindow :public QMainWindow {

	Q_OBJECT

public:
	MainWindow();
    ~MainWindow();

private:
	QMenu *fileMenu, *picMenu;
	QAction *openFileAction, *saveFileAction, *dragAction, *clearAction;
	QList<QAction *> pluginActions;
	QActionGroup *fileGroup, *picGroup;

	QList<Shape *> shapeList; // ģ�����ͱ����� (Shape *), ʹ�û���ָ��ָ���������, ͨ���麯��ʵ�ֶ�̬
	QList<Shape *> tempShapeList;
	Shape *shapeDrawed = NULL; // ��ǰ�����ƵĶ���
	int curProcNo = -1; // ��ǰ����ָ���б�ı��, �� slot getShapeInstance() ����, �Ա�����ͷź���ú���������
	int shapeDraggedNo = -1; // ��Ҫ��ק�� shape �� shapeList �еı��
	bool fDrag = false; // �Ƿ����϶�ģʽ
	MenuActionFactory* menuActionFactory = NULL;
	ShapeFactory* shapeFactory = NULL;
	Painter* painter = NULL;
	PainterFactory* painterFactory = NULL;
	File *myFile;

	void createMenus();
	void createActions();
	void paintEvent(QPaintEvent *evt) override;
	void mousePressEvent(QMouseEvent *evt) override;
	void mouseMoveEvent(QMouseEvent *evt) override;
	void mouseReleaseEvent(QMouseEvent *evt) override;
	void mouseDoubleClickEvent(QMouseEvent *evt) override;

	void getShapeInstance();
	int Find(QPoint &point); // ������Ҫ����ק��ͼ�α��

private slots:
	void init();
	void setDrag();
	void clear(); // ����
	void saveFile();
	void openFile();
};

#endif // MAINWINDOW_H