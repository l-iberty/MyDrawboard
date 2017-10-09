#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "rectangle_global.h"
#include "..\..\Common\shape.h"

class Rectangle :public Shape {
public:
    Rectangle();
    ~Rectangle();

    void setRect() override;
    void draw(QPaintDevice *device) override;
    void drag(QMouseEvent *evt, QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    void addKeyPoints(QMouseEvent *evt) override;
    void addKeyPoints(QPoint &point) override;
    void clearKeyPoints() override;
    void setP1(QPoint &point) override;
    void setP2(QPoint &point) override;
    QString getDllModName() override;
};

#endif // RECTANGLE_H
