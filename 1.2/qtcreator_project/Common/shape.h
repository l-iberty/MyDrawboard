#ifndef SHAPE_H
#define SHAPE_H
#include <QtGui/QPainter>
#include <QtGui/QtEvents>

class Shape {
protected:
    QRegion region;
    QRect rect;
    QPoint *p1, *p2; // 用于拖拽模式

public:
    QVector<QPoint> keyPoints; // 决定图形位置的关键点

    virtual void setRect() = 0;
    virtual void draw(QPaintDevice *device) = 0; // device 指明需要在哪个设备(部件)上进行绘制
    virtual void drag(QMouseEvent *evt, QPaintDevice *device) = 0;
    virtual bool contains(QPoint &point) = 0;
    virtual void addKeyPoints(QMouseEvent *evt) = 0;
    virtual void addKeyPoints(QPoint &point) = 0;
    virtual void clearKeyPoints() = 0;
    virtual void setP1(QPoint &point) = 0;
    virtual void setP2(QPoint &point) = 0;
    virtual QString getDllModName() = 0;
};

#endif // SHAPE_H
