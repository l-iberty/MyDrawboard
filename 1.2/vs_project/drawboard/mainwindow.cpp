#include "mainwindow.h"
#include <Windows.h>
#include "file.h"

MainWindow::MainWindow() {
	resize(800, 560);
	menuActionFactory = new MenuActionFactory();
	shapeFactory = new ShapeFactory();
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
	
	int num = menuActionFactory->getMenuActionNum();
	for (int i = 0;i < num;i++) {
		QAction *action = menuActionFactory->createMenuAction(i, this);
		action->setCheckable(true);
		action->setData(i); // ���ñ��
		connect(action, SIGNAL(triggered()), this, SLOT(getShapeInstance()));
		pluginActions.push_back(action);
	}
}

void MainWindow::paintEvent(QPaintEvent *evt) {
	// ������ʱ����, ʵ�ֶ�̬����Ч��
	for (int i = 0;i < tempShapeList.size();i++) {
		tempShapeList.at(i)->draw(this);
	}
	
	// ��ʾ֮ǰ���Ƶ�ͼ��
	for (int i = 0;i < shapeList.size();i++) {
		shapeList.at(i)->draw(this);
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *evt) {
	if (fDrag &&
		shapeDraggedNo >= 0) {
		// ��קģʽ
		Shape *curShape = shapeList.at(shapeDraggedNo);
		curShape->setP2(evt->pos());
		curShape->drag(evt, this);
		// �ؼ����: ���� P1
		curShape->setP1(evt->pos());
	}
	else if (!fDrag &&
		shapeDrawed != NULL) {
		// �滭ģʽ
		shapeDrawed->addKeyPoints(evt);

		// shapeDrawed ��ӽ���ʱ������Ϊ�˼�ʱ��ʾ.
		// Ϊʵ�ֶ�̬����Ч��, ����ʹ��ǳ����.
		// ��̬���ƹ��̻����������ͬ����ʱ����, ʹ����ʱ�������,����
		// ��קʱ����ͬһλ�öѻ�����ͬ�Ķ���, �����"��������ק"�ļ���.
		tempShapeList.push_back(shapeDrawed);

		shapeDrawed->draw(this);
	}
	repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *evt) {
	// ��갴��, ����/�϶����̿�ʼ
	if (fDrag &&
		!shapeList.empty()) {
		// ��קģʽ
		setMouseTracking(false);
		shapeDraggedNo = Find(evt->pos());
		if (shapeDraggedNo >= 0)
			shapeList.at(shapeDraggedNo)->setP1(evt->pos());
	}
	else if (!fDrag) {
		// �滭ģʽ
		setMouseTracking(true);
		getShapeInstance2();
		shapeDrawed->addKeyPoints(evt->pos());
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *evt) {
	
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *evt) {
	// ˫�������ɻ���

	setMouseTracking(false);

	// �� shapeDrawed ����������� shapeList ����, �����´λ���ʱ��
	// �ϴλ���ͼ�λ���ʧ.
	// ע��, ���ڴ��ݸ� QList::push_back() �Ĳ�����ָ��, ������ɵ���Ӳ���
	// ��ǳ����, ��� "shapeList.push_back(shapeDrawed);" ������ Bug, ��
	// ʹ�����.

	if (!tempShapeList.empty() &&
		(curProcNo >= 0) &&
		(shapeDrawed != NULL)) {

		Shape *dulShape = shapeFactory->createDulShape(curProcNo, *shapeDrawed);
		// shapeList ������ջ��ƽ��
		shapeList.push_back(dulShape);

		shapeDrawed->clearKeyPoints();
		delete shapeDrawed; // shapeDrawed �� tempShapeList �е�����Ԫ�ض�ָ��ͬһ������, ֻ������һ��
		shapeDrawed = NULL;
		tempShapeList.clear(); // ����䲻��������������
	}
}

void MainWindow::getShapeInstance2() {
	// shapeDrawed ָ��Ķ������������������ɲ���ȡ Shape ʵ��
	if (shapeDrawed == NULL &&
		curProcNo >= 0) {
		shapeDrawed = shapeFactory->createShape(curProcNo);
	}
}

int MainWindow::Find(QPoint &point) {
	// �����ҵ�����Ҫ������ק��ͼ�α��, δ�ҵ��򷵻�(-1)
	for (int i = 0;i < shapeList.size();i++) {
		if (shapeList.at(i)->contains(point))
			return i;
	}
	return -1;
}

// slot function
void MainWindow::getShapeInstance() {
	fDrag = false; // �˳���קģʽ
	setCursor(Qt::ArrowCursor);

	QAction *actionTriggered = qobject_cast<QAction *>(sender());
	curProcNo = actionTriggered->data().toInt();

	// ��� Shape ʵ��, ׼������
	shapeDrawed = shapeFactory->createShape(curProcNo);
}

// slot function
void MainWindow::setDrag() {
	fDrag = true; // ������קģʽ
	setCursor(Qt::ClosedHandCursor);
}

// slot function
void MainWindow::clear() {
	fDrag = false; // �˳���קģʽ
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