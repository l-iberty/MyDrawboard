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

	// File ѡ��
	fileMenu = menuBar()->addMenu(tr("File"));
	openFileAction = new QAction(tr("Open"), this);
	saveFileAction = new QAction(tr("Save"), this);
	fileGroup = new QActionGroup(this);
	fileMenu->addAction(fileGroup->addAction(openFileAction));
	fileMenu->addAction(fileGroup->addAction(saveFileAction));
	connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));

	// Picture ѡ�� (ͬʱ���ز��)
	picMenu = menuBar()->addMenu(tr("Picture"));
	picGroup = new QActionGroup(this);
	
	PluginLoader plugloader = PluginLoader(PLUGIN_DIR);
	dll_names = plugloader.getDllFileNames();
	plugin_names = plugloader.getPluginNames();
	
	for (int i = 0;i < plugin_names.size();i++) {
		// ���ò˵���
		QAction *action = new QAction(tr(plugin_names[i].c_str()), this);
		action->setCheckable(true);
		action->setData(i); // ���ñ��
		picMenu->addAction(picGroup->addAction(action));
		connect(action, SIGNAL(triggered()), this, SLOT(getShapeInstance()));

		// ���� DLL, ȡ�ú���ָ��
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
		(shapeDragedNo >= 0)) {
		// ��קģʽ
		Shape *curShape = shapeList.at(shapeDragedNo);
		Painter *painter = new Painter(curShape);
		curShape->setP2(evt->pos());
		painter->drag(evt, this);
		// �ؼ����: ���� P1
		curShape->setP1(evt->pos());
	}
	else if (!fDrag && shapeDrawed != NULL) {
		// �滭ģʽ
		// ���õڶ����ؼ���
		shapeDrawed->setKeyP2(evt->pos());

		// shapeDrawed ��ӽ���ʱ������Ϊ�˼�ʱ��ʾ.
		// Ϊʵ�ֶ�̬����Ч��, ����ʹ��ǳ����.
		// ��̬���ƹ��̻����������ͬ����ʱ����, ʹ����ʱ�������,
		// ������קʱ����ͬһλ�öѻ�����ͬ�Ķ���, �����"��������ק"
		// �ļ���.
		tempShapeList.push_back(shapeDrawed);

		Painter *painter = new Painter(shapeDrawed);
		painter->draw(this);
	}
	repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *evt) {
	// ��갴��, ����/�϶����̿�ʼ
	if (fDrag &&
		!shapeList.empty()) {
		// ��קģʽ
		// Find the shape needed to be dragged.
		for (int i = 0;i < shapeList.size();i++) {
			if (shapeList.at(i)->contains(evt->pos())) {
				shapeList.at(i)->setP1(evt->pos());
				shapeDragedNo = i;
				break; // Found it
			}
			else {
				// �ؼ����: �����ȥӰ������
				shapeDragedNo = -1; // Not Found
			}
		}
	}
	else if (!fDrag && shapeDrawed != NULL) {
		// �滭ģʽ
		// ���õ�һ���ؼ���
		shapeDrawed->setKeyP1(evt->pos());
	}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *evt) {
	// �� shapeDrawed ����������� shapeList ����, �����´λ���ʱ��
	// �ϴλ���ͼ�λ���ʧ.
	// ע��, ���ڴ��ݸ� QList::push_back() �Ĳ�����ָ��, ������ɵ���Ӳ���
	// ��ǳ����, ��� "shapeList.push_back(shapeDrawed);" ������ Bug, ��
	// ʹ�����.
	
	if (!proc_getDulShapeInstance_list.empty() &&
		!tempShapeList.empty() &&
		(curProcNo >= 0) &&
		(shapeDrawed != NULL)) {

		PPROC_GETDULSHAPEINSTANCE getDulShapeInstance = proc_getDulShapeInstance_list.at(curProcNo);
		Shape *dulShape = getDulShapeInstance(*shapeDrawed);
		// shapeList ������ջ��ƽ��
		shapeList.push_back(dulShape);

		// �����ʱ����
		tempShapeList.clear();
	}
}

// slot function
void MainWindow::getShapeInstance() {
	fDrag = false; // �˳���קģʽ
	setCursor(Qt::ArrowCursor);

	QAction *actionTriggered = qobject_cast<QAction *>(sender());
	int i = actionTriggered->data().toInt();
	curProcNo = i;

	// ȡ�ö�Ӧ�ĺ���ָ��, ��� Shape ʵ��, ׼������
	if (!proc_instance_list.empty()) {
		PPROC_INSTANCE instance = proc_instance_list.at(i);
		if (instance != NULL) {
			shapeDrawed = instance();
		}
	}
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