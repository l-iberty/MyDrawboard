#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "file.h"
#include "menuactionfactory.h"
#include "painter.h"
#include "painterfactory.h"
#include "pluginloader.h"
#include "shape.h"
#include <QtGui/QtEvents>
#include <QtWidgets/QAction>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>

typedef PainterFactory *(*PLUGIN_PROC)();

class Shape;

class MainWindow : public QMainWindow {

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
  void initPlugins();
  void putPainter(Painter *pPainter);
  void merge(Painter *pPainter);
private slots:
  void init();
  void setDragMode();
  void clear(); // 清屏
  void saveFile();
  void openFile();

private:
  // UI
  QMenu *m_pFileMenu, *m_pPicMenu;
  QAction *m_pOpenFileAction, *m_pSaveFileAction, *m_pDragAction, *m_pClearAction;
  QList<QAction *> m_PluginActionList;
  QActionGroup *m_pFileGroup, *m_pPicGroup;
  // Misc
  PluginLoader m_PluginLoader;
  QList<PLUGIN_PROC> m_PluginProcList;
  int m_PluginNo;
  bool m_IsDragMode;
  bool m_DragEnabled;
  Painter *m_pCurrentPainter;
  QList<Painter *> m_PainterList;
};

#endif // MAINWINDOW_H