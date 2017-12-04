#ifndef POLYGON_PAINTER_H
#define POLYGON_PAINTER_H

#include "polygon.h"
#include "polygonfactory.h"
#include "../../Common/painter.h"

class PolygonPainter :public MyPolygon, public Painter {
public:
    PolygonPainter();
    ~PolygonPainter();
    void handleMouseMovePoint(QMouseEvent *evt) override;
    void draw(QPaintDevice *device) override;
    void draw(Shape *shape, QPaintDevice *device) override;
private:
    QPoint m_MovingPoint;
};

#endif // POLYGON_PAINTER_H
