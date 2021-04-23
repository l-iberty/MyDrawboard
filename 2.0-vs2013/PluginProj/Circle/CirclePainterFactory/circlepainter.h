#ifndef CIRCLEPAINTER_H
#define CIRCLEPAINTER_H

#include "../../Common/painter.h"
#include "circle.h"
#include "circlefactory.h"

class CirclePainter : public MyCircle, public Painter {
public:
  CirclePainter();
  ~CirclePainter();
  void getFactoryFileName(char *pszFileName) override;
  void handleMouseMovePoint(QMouseEvent *evt) override;
  void handleMousePressPoint(QPoint &point) override;
  void draw(QPaintDevice *device) override;
  void draw(Shape *shape, QPaintDevice *device) override;
};

#endif // CIRCLEPAINTER_H
