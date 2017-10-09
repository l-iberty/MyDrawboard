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

#endif // CIRCLE_H
