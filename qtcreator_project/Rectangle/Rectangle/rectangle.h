#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "rectangle_global.h"
#include "..\..\Common\shape.h"

class Rectangle :public Shape {
public:
    Rectangle();
    ~Rectangle();
    void draw(QPaintDevice *device) override; // device 指明需要在哪个设备(部件)上进行绘制
    void drag(QMouseEvent *evt, QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    void setKeyP1(QPoint &point) override;
    void setKeyP2(QPoint &point) override;
    void setP1(QPoint &point) override;
    void setP2(QPoint &point) override;
    QString getDllModName() override;
};

#endif // RECTANGLE_H
