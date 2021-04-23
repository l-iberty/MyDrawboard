#ifndef POLYGON_H
#define POLYGON_H

#include "../../Common/shape.h"

class MyPolygon : public Shape {
public:
  MyPolygon();
  ~MyPolygon();
  void setKeyPoints(QVector<QPoint> &keyPoints) override;
  bool contains(QPoint &point) override;
  void setPolygon(QVector<QPoint> &points);
  QPolygon &getPolygon();

protected:
  QPolygon m_Polygon;
};

#endif // POLYGON_H
