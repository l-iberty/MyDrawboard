#include "mainwindow.h"
#include <QtWidgets\qaction.h>
#include <QtWidgets\qmenu.h>
#include <QtWidgets\qmenubar.h>
#include <QtGui\qpen.h>
#include <QtGui\qpainter.h>
#include <Windows.h>
#include "painter.h"
#include "file.h"

#ifndef PLUGIN_DIR
#define PLUGIN_DIR ".\\plugins\\*"
#endif

#ifndef PROC_INSTANCE
#define PROC_INSTANCE "?instance@@YAPAVShape@@XZ"
#endif

#ifndef PROC_GETDULSHAPEINSTANCE
#define PROC_GETDULSHAPEINSTANCE "?getDulShapeInstance@@YAPAVShape@@AAV1@@Z"
#endif

MainWindow::MainWindow() {
	setSize(700, 500);
	createMenusAndLoadplugins();
}

MainWindow::~MainWindow() {

}

void MainWindow::setSize(int width, int height) {
	resize(width, height);
}

void MainWindow::createMenusAndLoadplugins() {
	QMenu *fileMenu, *picMenu;
	QAction *openFileAction, *saveFileAction, *dragAction;
	QActionGroup *fileGroup, *picGroup;

	// File 选项
	fileMenu = menuBar()->addMenu(tr("File"));
	openFileAction = new QAction(tr("Open"), this);
	saveFileAction = new QAction(tr("Save"), this);
	fileGroup = new QActionGroup(this);
	fileMenu->addAction(fileGroup->addAction(openFileAction));
	fileMenu->addAction(fileGroup->addAction(saveFileAction));
	connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));

	// Picture 选项 (同时加载插件)
	picMenu = menuBar()->addMenu(tr("Picture"));
	picGroup = new QActionGroup(this);
	
	PluginLoader plugloader = PluginLoader(PLUGIN_DIR);
	dll_names = plugloader.getDllFileNames();
	plugin_names = plugloader.getPluginNames();
	
	for (int i = 0;i < plugin_names.size();i++) {
		// 设置菜单项
		QAction *action = new QAction(tr(plugin_names[i].c_str()), this);
		action->setCheckable(true);
		action->setData(i); // 设置编号
		picMenu->addAction(picGroup->addAction(action));
		connect(action, SIGNAL(triggered()), this, SLOT(getShapeInstance()));

		// 加载 DLL, 取得函数指针
		HMODULE hInstDll = LoadLibraryA(dll_names.at(i).c_str());
		if (hInstDll != NULL) {
			PPROC_INSTANCE proc_instance = (PPROC_INSTANCE)GetProcAddress(
				hInstDll, PROC_INSTANCE);
			PPROC_GETDULSHAPEINSTANCE proc_getDulShapeInstance = (PPROC_GETDULSHAPEINSTANCE)GetProcAddress(
				hInstDll, PROC_GETDULSHAPEINSTANCE);
			if (proc_instance && proc_getDulShapeInstance) {
				proc_instance_list.push_back(proc_instance);
				proc_getDulShapeInstance_list.push_back(proc_getDulShapeInstance);
			}
			else
				MessageBoxA(0, "GetProcAddress Failed", "ERROR", MB_ICONERROR);
		}
		else {
			MessageBoxA(0, "LoadLibraryA Failed", "ERROR", MB_ICONERROR);
		}
	}
	
	picMenu->addSeparator();
	dragAction = new QAction(tr("drag"), this);
	dragAction->setCheckable(true);
	picMenu->addAction(picGroup->addAction(dragAction));
	connect(dragAction, SIGNAL(triggered()), this, SLOT(setDrag()));

	picMenu->addSeparator();
	dragAction = new QAction(tr("clear"), this);
	dragAction->setCheckable(true);
	picMenu->addAction(picGroup->addAction(dragAction));
	connect(dragAction, SIGNAL(triggered()), this, SLOT(clear()));
}

void MainWindow::paintEvent(QPaintEvent *evt) {
	// 遍历临时容器, 实现动态绘制效果
	for (int i = 0;i < tempShapeList.size();i++) {
		tempShapeList.at(i)->draw(this);
	}
	
	// 显示之前绘制的图形
	for (int i = 0;i < shapeList.size();i++) {
		shapeList.at(i)->draw(this);
	}
}


void MainWindow::mouseMoveEvent(QMouseEvent *evt) {
	if (fDrag &&
		(shapeDragedNo >= 0)) {
		// 拖拽模式
		Shape *curShape = shapeList.at(shapeDragedNo);
		Painter *painter = new Painter(curShape);
		curShape->setP2(evt->pos());
		painter->drag(evt, this);
		// 关键语句: 重置 P1
		curShape->setP1(evt->pos());
	}
	else if (!fDrag && shapeDrawed != NULL) {
		// 绘画模式
		// 设置第二个关键点
		shapeDrawed->setKeyP2(evt->pos());

		// shapeDrawed 添加进临时容器是为了即时显示.
		// 为实现动态绘制效果, 必须使用浅拷贝.
		// 动态绘制过程会产生大量相同的临时对象, 使用临时容器存放,
		// 否则拖拽时由于同一位置堆积了相同的对象, 会产生"拷贝性拖拽"
		// 的假象.
		tempShapeList.push_back(shapeDrawed);

		Painter *painter = new Painter(shapeDrawed);
		painter->draw(this);
	}
	repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *evt) {
	// 鼠标按下, 绘制/拖动过程开始
	if (fDrag &&
		!shapeList.empty()) {
		// 拖拽模式
		// Find the shape needed to be dragged.
		for (int i = 0;i < shapeList.size();i++) {
			if (shapeList.at(i)->contains(evt->pos())) {
				shapeList.at(i)->setP1(evt->pos());
				shapeDragedNo = i;
				break; // Found it
			}
			else {
				// 关键语句: 避免过去影响现在
				shapeDragedNo = -1; // Not Found
			}
		}
	}
	else if (!fDrag && shapeDrawed != NULL) {
		// 绘画模式
		// 设置第一个关键点
		shapeDrawed->setKeyP1(evt->pos());
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *evt) {
	// 将 shapeDrawed 拷贝后添加至 shapeList 容器, 否则下次画的时候
	// 上次画的图形会消失.
	// 注意, 由于传递给 QList::push_back() 的参数是指针, 所以完成的添加操作
	// 是浅拷贝, 语句 "shapeList.push_back(shapeDrawed);" 将导致 Bug, 须
	// 使用深拷贝.
	
	if (!proc_getDulShapeInstance_list.empty() &&
		!tempShapeList.empty() &&
		(curProcNo >= 0) &&
		(shapeDrawed != NULL)) {

		PPROC_GETDULSHAPEINSTANCE getDulShapeInstance = proc_getDulShapeInstance_list.at(curProcNo);
		Shape *dulShape = getDulShapeInstance(*shapeDrawed);
		// shapeList 存放最终绘制结果
		shapeList.push_back(dulShape);

		// 清空临时容器
		tempShapeList.clear();
	}
}

// slot function
void MainWindow::getShapeInstance() {
	fDrag = false; // 退出拖拽模式
	setCursor(Qt::ArrowCursor);

	QAction *actionTriggered = qobject_cast<QAction *>(sender());
	int i = actionTriggered->data().toInt();
	curProcNo = i;

	// 取得对应的函数指针, 获得 Shape 实例, 准备绘制
	if (!proc_instance_list.empty()) {
		PPROC_INSTANCE instance = proc_instance_list.at(i);
		if (instance != NULL) {
			shapeDrawed = instance();
		}
	}
}

// slot function
void MainWindow::setDrag() {
	fDrag = true; // 进入拖拽模式
	setCursor(Qt::ClosedHandCursor);
}

// slot function
void MainWindow::clear() {
	fDrag = false; // 退出拖拽模式
	setCursor(Qt::ArrowCursor);

	shapeList.clear();
	tempShapeList.clear();
	repaint();
}

// slot function
void MainWindow::saveFile() {
	myFile = new File(shapeList);
	if (myFile->save())
		MessageBoxA(0, "File saved successfully!", "Save File", MB_OK);
	else
		MessageBoxA(0, "Cannot save file!", "ERROR", MB_OK);

	delete myFile;
}

// slot function
void MainWindow::openFile() {
	myFile = new File(shapeList);
	if (myFile->open()) {
		shapeList = myFile->getFileData();
		repaint();
	}
	else {
		MessageBoxA(0, "Cannot open file!", "ERROR", MB_ICONERROR);
	}
	delete myFile;
}