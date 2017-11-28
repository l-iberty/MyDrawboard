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

    void draw(QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    void addKeyPoints(QMouseEvent *evt) override;
    QString getDllModName() override;
};

#endif // POLYGON_H
