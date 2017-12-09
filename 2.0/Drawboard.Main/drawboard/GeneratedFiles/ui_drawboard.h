/********************************************************************************
** Form generated from reading UI file 'drawboard.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWBOARD_H
#define UI_DRAWBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_drawboardClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *drawboardClass)
    {
        if (drawboardClass->objectName().isEmpty())
            drawboardClass->setObjectName(QStringLiteral("drawboardClass"));
        drawboardClass->resize(600, 400);
        menuBar = new QMenuBar(drawboardClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        drawboardClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(drawboardClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        drawboardClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(drawboardClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        drawboardClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(drawboardClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        drawboardClass->setStatusBar(statusBar);

        retranslateUi(drawboardClass);

        QMetaObject::connectSlotsByName(drawboardClass);
    } // setupUi

    void retranslateUi(QMainWindow *drawboardClass)
    {
        drawboardClass->setWindowTitle(QApplication::translate("drawboardClass", "drawboard", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class drawboardClass: public Ui_drawboardClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWBOARD_H
