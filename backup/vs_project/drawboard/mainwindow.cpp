#include "mainwindow.h"
#include <Windows.h>
//#include "file.h"

MainWindow::MainWindow() {
	m_pFileMenu =			NULL;
	m_pPicMenu =			NULL;
	m_pOpenFileAction =		NULL;
	m_pSaveFileAction =		NULL;
	m_pDragAction =			NULL;
	m_pClearAction =		NULL;
	m_pFileGroup =			NULL;
	m_pPicGroup =			NULL;
	m_CurProcNo = 			-1;
	m_IsDragMode = 			false;
	m_DragEnabled = 		false;
	m_pMenuActionFactory =	NULL;
	m_pPainter = 			NULL;
	m_pPainterFactory = 	NULL;

	resize(800, 560);
	m_pMenuActionFactory = new MenuActionFactory();
	createActions();
	createMenus();
	initPluginProcList();
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
	if (m_pMenuActionFactory != NULL)	{ delete m_pMenuActionFactory; }
	if (m_pPainter != NULL)				{ delete m_pPainter; }
	if (m_pPainterFactory != NULL)		{ delete m_pPainterFactory; }

	for (int i = 0;i < m_PluginActions.size();i++) {
		if (m_PluginActions.at(i) != NULL) {
			delete m_PluginActions.at(i);
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

	connect(m_pOpenFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(m_pSaveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(m_pDragAction, SIGNAL(triggered()), this, SLOT(setDragMode()));
	connect(m_pClearAction, SIGNAL(triggered()), this, SLOT(clear()));

	int num = m_pMenuActionFactory->getMenuActionNum();
	for (int i = 0;i < num;i++) {
		QAction *action = m_pMenuActionFactory->createMenuAction(i, this);
		action->setCheckable(true);
		action->setData(i); // ÉèÖÃ±àºÅ
		connect(action, SIGNAL(triggered()), this, SLOT(init()));
		m_PluginActions.push_back(action);
	}
}

void MainWindow::createMenus() {
	m_pFileMenu = menuBar()->addMenu(tr("File"));
	m_pFileGroup = new QActionGroup(this);
	m_pFileMenu->addAction(m_pFileGroup->addAction(m_pOpenFileAction));
	m_pFileMenu->addAction(m_pFileGroup->addAction(m_pSaveFileAction));

	m_pPicMenu = menuBar()->addMenu(tr("Picture"));
	m_pPicGroup = new QActionGroup(this);
	for (int i = 0;i < m_PluginActions.size();i++) {
		m_pPicMenu->addAction(m_pPicGroup->addAction(m_PluginActions.at(i)));
	}
	m_pPicMenu->addSeparator();
	m_pPicMenu->addAction(m_pPicGroup->addAction(m_pDragAction));
	m_pPicMenu->addSeparator();
	m_pPicMenu->addAction(m_pPicGroup->addAction(m_pClearAction));
}

void MainWindow::paintEvent(QPaintEvent *evt) {
	if (m_pPainter != NULL) {
		m_pPainter->drawAllShapes(this);
		m_pPainter->draw(this);
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt) {
	if (!m_IsDragMode) {
		m_pPainter->handleMouseMovePoint(evt);
	}
	else {
		if (m_DragEnabled) {
			m_pPainter->setEndPoint(evt->pos());
			m_pPainter->drag(this);
			m_pPainter->setStartPoint(evt->pos());
		}
	}
	repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *evt) {
	if (!m_IsDragMode) {
		setMouseTracking(true);
		m_pPainter->handleMousePressPoint(evt->pos());
	}
	else {
		Shape *shape = m_pPainter->find(evt->pos());
		if (shape != NULL) {
			m_DragEnabled = true;
			m_pPainter->setDraggingShape(shape);
			m_pPainter->setStartPoint(evt->pos());
		}
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *evt) {
	m_DragEnabled = false;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *evt) {
	setMouseTracking(false);
	m_pPainter->save();
}

void MainWindow::initPluginProcList() {
	PluginLoader pluginLoader;
	QList<HMODULE> hModList = pluginLoader.getDllModList();
	for (int i = 0;i < hModList.size();i++) {
		PLUGIN_PROC PainterFactoryInstance = (PLUGIN_PROC)
			GetProcAddress(hModList.at(i), "PainterFactoryInstance");
		if (PainterFactoryInstance != NULL) {
			m_PluginProcList.push_back(PainterFactoryInstance);
		}
	}
}

PainterFactory* MainWindow::getPainterFactory(int i) {
	PainterFactory* painterFactory = NULL;
	if (!m_PluginProcList.isEmpty()) {
		PLUGIN_PROC PainterFactoryInstance = m_PluginProcList.at(i);
		painterFactory = PainterFactoryInstance();
	}
	return painterFactory;
}

// slot function
void MainWindow::init() {
	m_IsDragMode = false;
	setCursor(Qt::ArrowCursor);

	QAction *actionTriggered = qobject_cast<QAction *>(sender());
	m_CurProcNo = actionTriggered->data().toInt();

	m_pPainterFactory = getPainterFactory(m_CurProcNo);
	m_pPainter = m_pPainterFactory->createPainter();
}

// slot function
void MainWindow::setDragMode() {
	m_IsDragMode = true;
	setCursor(Qt::ClosedHandCursor);
}

// slot function
void MainWindow::clear() {
	m_IsDragMode = false;
	m_pPainter->clearShapeList();
	setCursor(Qt::ArrowCursor);
	repaint();
}

// slot function
void MainWindow::saveFile() {
	/*myFile = new File(m_ShapeList);
	if (myFile->save()) {
		MessageBox(NULL, TEXT("File saved successfully!"), 
			TEXT("Save File"), MB_OK);
	}
	else {
		MessageBox(NULL, TEXT("Cannot save file!"), 
			TEXT("ERROR"), MB_ICONERROR);
	}
	delete myFile;*/
}

// slot function
void MainWindow::openFile() {
	/*myFile = new File(m_ShapeList);
	if (myFile->open()) {
		m_ShapeList = myFile->getFileData();
		repaint();
	}
	else {
		MessageBox(NULL, TEXT("Cannot open file!"), 
			TEXT("ERROR"), MB_ICONERROR);
	}
	delete myFile;*/
}
