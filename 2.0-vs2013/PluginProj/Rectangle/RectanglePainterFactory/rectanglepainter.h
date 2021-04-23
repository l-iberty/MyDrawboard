#ifndef RECTANGLEPAINTER_H
#define RECTANGLEPAINTER_H

#include "../../Common/painter.h"
#include "rectangle.h"
#include "rectanglefactory.h"

class RectanglePainter : public MyRectangle, public Painter {
public:
  RectanglePainter();
  ~RectanglePainter();
  void getFactoryFileName(char *pszFileName) override;
  void handleMouseMovePoint(QMouseEvent *evt) override;
  void handleMousePressPoint(QPoint &point) override;
  void draw(QPaintDevice *device) override;
  void draw(Shape *shape, QPaintDevice *device) override;
};

#endif // RECTANGLEPAINTER_H
