#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets/QMainWindow>
#include <QtGui/QtEvents>
#include <QtWidgets/QAction>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include "shape.h"
#include "menuactionfactory.h"
#include "painter.h"
#include "painterfactory.h"
#include "pluginloader.h"
//#include "file.h"

typedef PainterFactory* (*PLUGIN_PROC)();

class Shape;

class MainWindow :public QMainWindow {

	Q_OBJECT

public:
	MainWindow();
    ~MainWindow();
private:
	void createActions();
	void createMenus();
	void paintEvent(QPaintEvent *evt) override;
	void mousePressEvent(QMouseEvent *evt) override;
	void mouseMoveEvent(QMouseEvent *evt) override;
	void mouseReleaseEvent(QMouseEvent *evt) override;
	void mouseDoubleClickEvent(QMouseEvent *evt) override;
	void initPluginProcList();
	PainterFactory* getPainterFactory(int i);
private slots:
	void init();
	void setDragMode();
	void clear(); // «Â∆¡
	void saveFile();
	void openFile();
private:
	// UI
	QMenu *m_pFileMenu, *m_pPicMenu;
	QAction *m_pOpenFileAction, *m_pSaveFileAction, *m_pDragAction, *m_pClearAction;
	QList<QAction *> m_PluginActions;
	QActionGroup *m_pFileGroup, *m_pPicGroup;
	// Misc
	QList<PLUGIN_PROC> m_PluginProcList;
	int m_CurProcNo;
	bool m_IsDragMode;
	bool m_DragEnabled;
	MenuActionFactory* m_pMenuActionFactory;
	Painter* m_pPainter;
	PainterFactory* m_pPainterFactory;
};

#endif // MAINWINDOW_H