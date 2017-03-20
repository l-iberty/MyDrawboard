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
    QPoint *keyP1, *keyP2; // 决定图形位置的两个关键点

    virtual void draw(QPaintDevice *device) = 0;
    virtual void drag(QMouseEvent *evt, QPaintDevice *device) = 0;
    virtual bool contains(QPoint &point) = 0;
    virtual void setKeyP1(QPoint &point) = 0;
    virtual void setKeyP2(QPoint &point) = 0;
    virtual void setP1(QPoint &point) = 0;
    virtual void setP2(QPoint &point) = 0;
    virtual QString getDllModName() = 0;
};

#endif // SHAPE_H
