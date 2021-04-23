#ifndef POLYGON_PAINTER_H
#define POLYGON_PAINTER_H

#include "../../Common/painter.h"
#include "polygon.h"
#include "polygonfactory.h"

class PolygonPainter : public MyPolygon, public Painter {
public:
  PolygonPainter();
  ~PolygonPainter();
  void getFactoryFileName(char *pszFileName) override;
  void handleMouseMovePoint(QMouseEvent *evt) override;
  void handleMousePressPoint(QPoint &point) override;
  void draw(QPaintDevice *device) override;
  void draw(Shape *shape, QPaintDevice *device) override;

private:
  QPoint m_MovingPoint;
};

#endif // POLYGON_PAINTER_H
