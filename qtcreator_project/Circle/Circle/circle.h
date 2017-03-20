#ifndef CIRCLE_H
#define CIRCLE_H

#include "circle_global.h"
#include "..\..\Common\shape.h"

class Circle :public Shape {
private:
    int centerX;
    int centerY;
    int r;

public:
    Circle();
    ~Circle();
    void draw(QPaintDevice *device) override; // device 指明需要在哪个设备(部件)上进行绘制
    void drag(QMouseEvent *evt, QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    void setKeyP1(QPoint &point) override;
    void setKeyP2(QPoint &point) override;
    void setP1(QPoint &point) override;
    void setP2(QPoint &point) override;
    QString getDllModName() override;
};

#endif // CIRCLE_H
