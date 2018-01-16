#include "mainwindow.h"
#include <Windows.h>
#include <assert.h>

MainWindow::MainWindow() {
	m_pFileMenu =			NULL;
	m_pPicMenu =			NULL;
	m_pOpenFileAction =		NULL;
	m_pSaveFileAction =		NULL;
	m_pDragAction =			NULL;
	m_pClearAction =		NULL;
	m_pFileGroup =			NULL;
	m_pPicGroup =			NULL;
	m_PluginNo = 			-1;
	m_IsDragMode = 			false;
	m_DragEnabled = 		false;
	m_pCurrentPainter = 			NULL;

	resize(800, 560);
	createActions();
	createMenus();
	initPlugins();
}

MainWindow::~MainWindow() {
	if (m_pFileMenu != NULL)			{ delete m_pFileMenu; }
	if (m_pPicMenu != NULL)				{ delete m_pPicMenu; }
	if (m_pOpenFileAction != NULL)		{ delete m_pOpenFileAction; }
	if (m_pSaveFileAction != NULL)		{ delete m_pSaveFileAction; }
	if (m_pDragAction != NULL)			{ delete m_pDragAction; }
	if (m_pClearAction != NULL)			{ delete m_pClearAction; }
	if (m_pFileGroup != NULL)			{ delete m_pFileGroup; }
	if (m_pPicGroup != NULL)			{ delete m_pPicGroup; }

	assert(m_PluginActionList.size() == m_PainterList.size());
	for (int i = 0;i < m_PluginActionList.size();i++) {
		if (m_PluginActionList.at(i) && m_PainterList.at(i)) {
			delete m_PluginActionList.at(i);
			delete m_PainterList.at(i);
		}
	}
}

void MainWindow::createActions() {
	m_pOpenFileAction = new QAction(tr("Open"), this);
	m_pSaveFileAction = new QAction(tr("Save"), this);
	m_pDragAction = new QAction(tr("Drag"), this);
	m_pClearAction = new QAction(tr("Clear"), this);

	m_pOpenFileAction->setCheckable(true);
	m_pSaveFileAction->setCheckable(true);
	m_pDragAction->setCheckable(true);

	m_pOpenFileAction->setIcon(QIcon(QString(":/drawboard/Resources/open.png")));
	m_pSaveFileAction->setIcon(QIcon(QString(":/drawboard/Resources/save.png")));
	m_pDragAction->setIcon(QIcon(QString(":/drawboard/Resources/drag.png")));
	m_pClearAction->setIcon(QIcon(QString(":/drawboard/Resources/clear.png")));

	connect(m_pOpenFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(m_pSaveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(m_pDragAction, SIGNAL(triggered()), this, SLOT(setDragMode()));
	connect(m_pClearAction, SIGNAL(triggered()), this, SLOT(clear()));

	MenuActionFactory menuActionFactory = MenuActionFactory(m_PluginLoader);
	int num = menuActionFactory.getMenuActionNum();
	for (int i = 0;i < num;i++) {
		QAction *action = menuActionFactory.createMenuAction(i, this);
		action->setCheckable(true);
		action->setData(i); // 设置编号
		action->setIcon(*menuActionFactory.getMenuActionIcon(i));
		connect(action, SIGNAL(triggered()), this, SLOT(init()));
		m_PluginActionList.push_back(action);
	}
}

void MainWindow::createMenus() {
	m_pFileMenu = menuBar()->addMenu(tr("File"));
	m_pFileGroup = new QActionGroup(this);
	m_pFileMenu->addAction(m_pFileGroup->addAction(m_pOpenFileAction));
	m_pFileMenu->addAction(m_pFileGroup->addAction(m_pSaveFileAction));

	m_pPicMenu = menuBar()->addMenu(tr("Picture"));
	m_pPicGroup = new QActionGroup(this);
	for (int i = 0;i < m_PluginActionList.size();i++) {
		m_pPicMenu->addAction(m_pPicGroup->addAction(m_PluginActionList.at(i)));
	}
	m_pPicMenu->addSeparator();
	m_pPicMenu->addAction(m_pPicGroup->addAction(m_pDragAction));
	m_pPicMenu->addSeparator();
	m_pPicMenu->addAction(m_pPicGroup->addAction(m_pClearAction));
}

void MainWindow::paintEvent(QPaintEvent *evt) {
	// 重绘之前绘制的图形
	for (int i = 0;i < m_PainterList.size();i++) {
		Painter *pPainter = m_PainterList.at(i);
		if (pPainter != NULL) {
			pPainter->drawAllShapes(this);
		}
	}
	// 绘制当前图形
	if (m_pCurrentPainter != NULL) {
		m_pCurrentPainter->draw(this);
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt) {
	if (m_pCurrentPainter != NULL) {
		if (!m_IsDragMode) {
			m_pCurrentPainter->handleMouseMovePoint(evt);
		}
		else {
			if (m_DragEnabled) {
				m_pCurrentPainter->setEndPoint(evt->pos());
				m_pCurrentPainter->drag(this);
				m_pCurrentPainter->setStartPoint(evt->pos());
			}
		}
		repaint();
	}
}

void MainWindow::mousePressEvent(QMouseEvent *evt) {
	if (!m_IsDragMode && m_pCurrentPainter) { // 绘画模式
		setMouseTracking(true);
		m_pCurrentPainter->handleMousePressPoint(evt->pos());
	}
	else { // 拖动模式
		for (int i = 0;i < m_PainterList.size();i++) {
			Painter *pPainter = m_PainterList.at(i);
			Shape *pShape = pPainter->find(evt->pos());
			if (pShape != NULL) {
				m_DragEnabled = true;
				m_pCurrentPainter = pPainter;
				m_pCurrentPainter->setDraggingShape(pShape);
				m_pCurrentPainter->setStartPoint(evt->pos());
				break;
			}
		}
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *evt) {
	m_DragEnabled = false;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *evt) {
	setMouseTracking(false);
	if (m_pCurrentPainter != NULL) {
		m_pCurrentPainter->save();
	}
}

void MainWindow::initPlugins() {
	QList<HMODULE> pluginModuleList = m_PluginLoader.getDllModList();

	for (int i = 0;i < pluginModuleList.size();i++) {
		PLUGIN_PROC PainterFactoryInstance = (PLUGIN_PROC)
			GetProcAddress(pluginModuleList.at(i), "PainterFactoryInstance");
		if (PainterFactoryInstance != NULL) {
			m_PluginProcList.push_back(PainterFactoryInstance);
			Painter *pPainter = PainterFactoryInstance()->createPainter();
			if (pPainter != NULL)
				m_PainterList.push_back(pPainter);
		}
	}
}

void MainWindow::putPainter(Painter *pPainter) {
	if (pPainter != NULL) {
		if (!m_PainterList.contains(pPainter))
			merge(pPainter);
	}
}

// 来自插件 DLL 的 Painter 和来自文件的 Painter 都被放入 m_PainterList，
// 但 m_PainterList 中不能存在指向相同的 Painter 子类类型的指针，因此
// 需要进行合并.
void MainWindow::merge(Painter *pPainter) {
	char s1[MAX_PATH] = { 0 };
	char s2[MAX_PATH] = { 0 };

	pPainter->getFactoryFileName(s1);
	for (int i = 0;i < m_PainterList.size();i++) {
		m_PainterList.at(i)->getFactoryFileName(s2);
		if (!strcmp(s1, s2)) { // pPainter 和 m_PainterList.at(i) 指向的 Painter 子类的类型相同吗?
			delete m_PainterList.at(i);
			m_PainterList.replace(i, pPainter);
			break;
		}
	}
}

// slot function
void MainWindow::init() {
	m_IsDragMode = false;
	setCursor(Qt::ArrowCursor);
	m_pOpenFileAction->setDisabled(true); // 禁用菜单项 File->Open

	QAction *actionTriggered = qobject_cast<QAction *>(sender());
	m_PluginNo = actionTriggered->data().toInt();
	m_pCurrentPainter = m_PainterList.at(m_PluginNo);
}

// slot function
void MainWindow::setDragMode() {
	m_IsDragMode = true;
	setCursor(Qt::ClosedHandCursor);
}

// slot function
void MainWindow::clear() {
	m_IsDragMode = false;
	setCursor(Qt::ArrowCursor);

	for (int i = 0;i < m_PainterList.size();i++) {
		m_PainterList.at(i)->clearShapeList();
	}
	repaint();
}

// slot function
void MainWindow::saveFile() {
	Painter *pPainter = NULL;
	FileDataEntry fde = { 0 };

	QString name = QFileDialog::getSaveFileName();
	name.replace(QChar('/'), QString("\\"));
	File file(name, File::Save);

	for (int i = 0;i < m_PainterList.size();i++, fde = { 0 }) {
		pPainter = m_PainterList.at(i);
		QList<Shape*> shapeList = pPainter->getShapeList();
		if (!shapeList.isEmpty()) {
			// pPainter 由哪个 PainterFactory 创建?
			pPainter->getFactoryFileName(fde.szFileName);
			for (int k = 0;k < shapeList.size();k++) { // pPainter 一共画了多少个 Shape?
				// 获取每个 Shape 的点集
				QVector<QPoint> points = shapeList.at(k)->getKeyPoints();
				fde.pointsList.push_back(points);
			}
			file.save(&fde);
		}
	}
}

// slot function
void MainWindow::openFile() {
	FileDataEntry fde;
	int cb = 0, cbTotal = 0;

	QString name = QFileDialog::getOpenFileName();
	name.replace(QChar('/'), QString("\\"));
	File file(name, File::Open);
	
	for (;;fde = { 0 }) {
		cb = file.read(&fde, cbTotal);
		if (cb == 0)
			break;
		else
			cbTotal += cb;

		HMODULE hModule = GetModuleHandleA(fde.szFileName);
		if (hModule != NULL) {
			PLUGIN_PROC PainterFactoryInstance = (PLUGIN_PROC)
				GetProcAddress(hModule, "PainterFactoryInstance");
			if (PainterFactoryInstance != NULL) {
				Painter *pPainter = PainterFactoryInstance()->createPainter();
				if (pPainter != NULL) {
					for (int i = 0;i < fde.pointsList.size();i++) {
						QVector<QPoint> points = fde.pointsList.at(i);
						// Painter::save()保存到m_ShapeList里的是m_pDrawingShape指向的Shape，
						// 因此先调用Painter::setDrawingShape.
						pPainter->setDrawingShape(points);
						pPainter->save();
					}
					putPainter(pPainter);
				}
			}
		}
	}
	repaint();
}
