# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = drawboard
DESTDIR = ../Win32/Debug
QT += core widgets gui
CONFIG += debug
DEFINES += QT_DLL QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
win32:RC_FILE = drawboard.rc
HEADERS += ./file.h \
    ./menuactionfactory.h \
    ./painter.h \
    ./painterfactory.h \
    ./pluginloader.h \
    ./shape.h \
    ./shapefactory.h \
    ./drawboard.h \
    ./mainwindow.h \
    ./resource.h \
    ./resource1.h \
    ./resource2.h
SOURCES += ./drawboard.cpp \
    ./file.cpp \
    ./main.cpp \
    ./mainwindow.cpp \
    ./menuactionfactory.cpp \
    ./painter.cpp \
    ./painterfactory.cpp \
    ./pluginloader.cpp \
    ./shape.cpp \
    ./shapefactory.cpp
FORMS += ./drawboard.ui
RESOURCES += drawboard.qrc
RCC_FILE += Resource.rc
