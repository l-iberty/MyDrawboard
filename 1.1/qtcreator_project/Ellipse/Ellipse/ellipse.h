#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "ellipse_global.h"
#include "..\..\Common\shape.h"

class Ellipse :public Shape {
public:
    Ellipse();
    ~Ellipse();

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

#endif // ELLIPSE_H
