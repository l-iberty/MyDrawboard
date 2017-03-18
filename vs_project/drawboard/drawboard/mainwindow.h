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
	vector<string> dll_names; // DLL 文件的绝对路径
	vector<string> plugin_names; // 插件名
	QList<HMODULE> hModList; // DLL 模块句柄
	QList<PPROC_INSTANCE> proc_instance_list;
	QList<PPROC_GETDULSHAPEINSTANCE> proc_getDulShapeInstance_list;
	QList<Shape *> shapeList; // 模板类型必须是 (Shape *), 使用基类指针指向子类对象, 通过虚函数实现动态联编
	QList<Shape *> tempShapeList;
	Shape *shapeDrawed = NULL; // 当前被绘制的对象
	int curProcNo = -1; // 当前函数指针列表的编号, 由 slot getShapeInstance() 设置, 以便鼠标释放后调用函数完成深拷贝
	int shapeDragedNo = -1; // 需要拖拽的 shape 在 shapeList 中的编号
	bool fDrag = false; // 是否处在拖动模式
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
	void clear(); // 清屏
};

#endif // MAINWINDOW_H