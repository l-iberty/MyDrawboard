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

    virtual void setRect(QRect &rect) {
        this->rect.setTopLeft(rect.topLeft());
        this->rect.setBottomRight(rect.bottomRight());
    }

    virtual void addKeyPoints(QMouseEvent *evt) {
        if (keyPoints.size() <= 1) {
            keyPoints.push_back(evt->pos());
        }
        else {
            keyPoints.removeLast();
            keyPoints.push_back(evt->pos());
        }
    }

    virtual void addKeyPoints(QPoint &point) { keyPoints.push_back(point); }

    void clearKeyPoints() { keyPoints.clear(); }

    void setP1(QPoint &point) { p1 = new QPoint(point); }

    void setP2(QPoint &point) { p2 = new QPoint(point); }

    QPoint* getP1() { return p1; }

    QPoint* getP2() { return p2; }

    virtual void draw(QPaintDevice *device) = 0; // device 指明需要在哪个设备(部件)上进行绘制
    virtual bool contains(QPoint &point) = 0;
    virtual QString getDllModName() = 0;
};

#endif // SHAPE_H
