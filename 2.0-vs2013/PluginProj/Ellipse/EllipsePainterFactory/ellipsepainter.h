#ifndef ELLIPSEPAINTER_H
#define ELLIPSEPAINTER_H

#include "../../Common/painter.h"
#include "ellipse.h"
#include "ellipsefactory.h"

class EllipsePainter : public MyEllipse, public Painter {
public:
  EllipsePainter();
  ~EllipsePainter();
  void getFactoryFileName(char *pszFileName) override;
  void handleMouseMovePoint(QMouseEvent *evt) override;
  void handleMousePressPoint(QPoint &point) override;
  void draw(QPaintDevice *device) override;
  void draw(Shape *shape, QPaintDevice *device) override;
};

#endif // ELLIPSEPAINTER_H
