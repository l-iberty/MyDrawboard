#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "triangle_global.h"
#include "..\..\Common\shape.h"

class Triangle :public Shape {
private:
    QPolygon *triangle;

public:
    Triangle();
    ~Triangle();

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

#endif // TRIANGLE_H
