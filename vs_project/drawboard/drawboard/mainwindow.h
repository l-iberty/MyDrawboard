#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets\qmainwindow.h>
#include <QtGui\qevent.h>
#include <Windows.h>
#include "pluginloader.h"
#include "shape.h"

class Shape;

typedef Shape *(*PPROC_INSTANCE)();
typedef Shape *(*PPROC_GETDULSHAPEINSTANCE)(Shape &);

class MainWindow :public QMainWindow {

	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

private:
	vector<string> dll_names; // DLL �ļ��ľ���·��
	vector<string> plugin_names; // �����
	QList<HMODULE> hModList; // DLL ģ����
	QList<PPROC_INSTANCE> proc_instance_list;
	QList<PPROC_GETDULSHAPEINSTANCE> proc_getDulShapeInstance_list;
	QList<Shape *> shapeList; // ģ�����ͱ����� (Shape *), ʹ�û���ָ��ָ���������, ͨ���麯��ʵ�ֶ�̬����
	QList<Shape *> tempShapeList;
	Shape *shapeDrawed = NULL; // ��ǰ�����ƵĶ���
	int curProcNo = -1; // ��ǰ����ָ���б�ı��, �� slot getShapeInstance() ����, �Ա�����ͷź���ú���������
	int shapeDragedNo = -1; // ��Ҫ��ק�� shape �� shapeList �еı��
	bool fDrag = false; // �Ƿ����϶�ģʽ
	int mouseReleasedCount = 0;

	void setSize(int width, int height);
	void createMenusAndLoadplugins();
	void paintEvent(QPaintEvent *evt) override;
	void mousePressEvent(QMouseEvent *evt) override;
	void mouseMoveEvent(QMouseEvent *evt) override;
	void mouseReleaseEvent(QMouseEvent *evt) override;

private slots:
	void getShapeInstance();
	void setDrag();
	void clear(); // ����
};

#endif // MAINWINDOW_H