#-------------------------------------------------
#
# Project created by QtCreator 2017-12-02T16:45:31
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = PolygonPainterFactory
TEMPLATE = lib

DEFINES += POLYGONPAINTERFACTORY_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += polygonpainterfactory.cpp \
    polygon.cpp \
    polygonfactory.cpp \
    polygonpainter.cpp \
    ../../Common/painter.cpp \
    ../../Common/shape.cpp \
    ../../Common/shapefactory.cpp \
    ../../Common/painterfactory.cpp

HEADERS += polygonpainterfactory.h \
    ../../Common/global.h \
    ../../Common/painter.h \
    ../../Common/painterfactory.h \
    ../../Common/shape.h \
    ../../Common/shapefactory.h \
    polygonfactory.h \
    polygon.h \
    polygonpainter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    polygon.qrc
