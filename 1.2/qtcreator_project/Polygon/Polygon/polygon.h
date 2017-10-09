#ifndef POLYGON_H
#define POLYGON_H

#include "polygon_global.h"
#include "..\..\Common\shape.h"

class Polygon :public Shape {
private:
    QPolygon *polygon;
    QPoint movingPoint = QPoint(0, 0);

public:
    Polygon();
    ~Polygon();

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

#endif // POLYGON_H
