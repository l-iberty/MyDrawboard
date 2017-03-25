#include "mainwindow.h"
#include <Windows.h>
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
	resize(800, 560);
	loadPlugins();
	createActions();
	createMenus();
}

MainWindow::~MainWindow() {
	delete fileMenu;
	delete picMenu;
	delete openFileAction;
	delete saveFileAction;
	delete dragAction;
	delete clearAction;
	delete fileGroup;
	delete picGroup;

	for (int i = 0;i < pluginActions.size();i++)
		delete pluginActions.at(i);
}

void MainWindow::loadPlugins() {
	PluginLoader plugloader = PluginLoader(PLUGIN_DIR);
	dll_names = plugloader.getDllFileNames();
	plugin_names = plugloader.getPluginNames();

	for (int i = 0;i < plugin_names.size();i++) {
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
		else
			MessageBoxA(0, "Cannot load library!", "ERROR", MB_ICONERROR);
	}
}

void MainWindow::createMenus() {
	fileMenu = menuBar()->addMenu(tr("File"));
	fileGroup = new QActionGroup(this);
	fileMenu->addAction(fileGroup->addAction(openFileAction));
	fileMenu->addAction(fileGroup->addAction(saveFileAction));

	picMenu = menuBar()->addMenu(tr("Picture"));
	picGroup = new QActionGroup(this);
	for (int i = 0;i < pluginActions.size();i++) {
		picMenu->addAction(picGroup->addAction(pluginActions.at(i)));
	}
	picMenu->addSeparator();
	picMenu->addAction(picGroup->addAction(dragAction));
	picMenu->addSeparator();
	picMenu->addAction(picGroup->addAction(clearAction));
}

void MainWindow::createActions() {
	openFileAction = new QAction(tr("Open"), this);
	saveFileAction = new QAction(tr("Save"), this);
	dragAction = new QAction(tr("Drag"), this);
	clearAction = new QAction(tr("Clear"), this);
	
	openFileAction->setCheckable(true);
	saveFileAction->setCheckable(true);
	dragAction->setCheckable(true);

	connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(dragAction, SIGNAL(triggered()), this, SLOT(setDrag()));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clear()));
	
	for (int i = 0;i < plugin_names.size();i++) {
		QAction *action = new QAction(tr(plugin_names[i].c_str()), this);
		action->setCheckable(true);
		action->setData(i); // 设置编号
		connect(action, SIGNAL(triggered()), this, SLOT(getShapeInstance()));
		pluginActions.push_back(action);
	}
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
		shapeDraggedNo >= 0) {
		// 拖拽模式
		Shape *curShape = shapeList.at(shapeDraggedNo);
		curShape->setP2(evt->pos());
		curShape->drag(evt, this);
		// 关键语句: 重置 P1
		curShape->setP1(evt->pos());
	}
	else if (!fDrag &&
		shapeDrawed != NULL) {
		// 绘画模式
		shapeDrawed->addKeyPoints(evt);

		// shapeDrawed 添加进临时容器是为了即时显示.
		// 为实现动态绘制效果, 必须使用浅拷贝.
		// 动态绘制过程会产生大量相同的临时对象, 使用临时容器存放,否则
		// 拖拽时由于同一位置堆积了相同的对象, 会产生"拷贝性拖拽"的假象.
		tempShapeList.push_back(shapeDrawed);

		shapeDrawed->draw(this);
	}
	repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *evt) {
	// 鼠标按下, 绘制/拖动过程开始
	if (fDrag &&
		!shapeList.empty()) {
		// 拖拽模式
		setMouseTracking(false);
		shapeDraggedNo = Find(evt->pos());
		if (shapeDraggedNo >= 0)
			shapeList.at(shapeDraggedNo)->setP1(evt->pos());
	}
	else if (!fDrag) {
		// 绘画模式
		setMouseTracking(true);
		getShapeInstance2();
		shapeDrawed->addKeyPoints(evt->pos());
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *evt) {
	
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *evt) {
	// 双击鼠标完成绘制

	setMouseTracking(false);

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

		shapeDrawed->clearKeyPoints();
		delete shapeDrawed; // shapeDrawed 和 tempShapeList 中的所有元素都指向同一个对象, 只需析构一次
		shapeDrawed = NULL;
		tempShapeList.clear(); // 该语句不会引发对象析构
	}
}

void MainWindow::getShapeInstance2() {
	// shapeDrawed 指向的对象析构后需重新生成并获取 Shape 实例

	if (shapeDrawed == NULL &&
		curProcNo >= 0) {
		PPROC_INSTANCE instance = proc_instance_list.at(curProcNo);
		if (instance != NULL)
			shapeDrawed = instance();
	}
}

int MainWindow::Find(QPoint &point) {
	// 返回找到的需要进行拖拽的图形编号, 未找到则返回(-1)
	for (int i = 0;i < shapeList.size();i++) {
		if (shapeList.at(i)->contains(point))
			return i;
	}
	return -1;
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