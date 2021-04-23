#ifndef PAINTER_H
#define PAINTER_H

#include "shape.h"
#include "shapefactory.h"
#include <QIcon>
#include <QtCore/QList>

class Painter {
public:
  Painter();
  virtual ~Painter();
  virtual void getFactoryFileName(char *pszFileName) = 0;
  virtual void handleMouseMovePoint(QMouseEvent *evt) = 0;
  virtual void handleMousePressPoint(QPoint &point) = 0;
  virtual void draw(QPaintDevice *device) = 0;
  virtual void draw(Shape *shape, QPaintDevice *device) = 0;
  void drag(QPaintDevice *device);
  Shape *find(QPoint &point);
  void save();
  void setDrawingShape(QVector<QPoint> &keyPoints);
  void setDraggingShape(Shape *shape);
  void setStartPoint(QPoint &point);
  void setEndPoint(QPoint &point);
  QPoint &getStartPoint();
  QPoint &getEndPoint();
  QList<Shape *> &getShapeList();
  Shape *getShapeListItem(int i);
  bool isEmptyShapeList();
  void clearShapeList();
  void drawAllShapes(QPaintDevice *device);

protected:
  Shape *m_pDrawingShape;
  Shape *m_pDraggingShape;
  QPoint m_StartPoint, m_EndPoint;
  QList<Shape *> m_ShapeList;
  ShapeFactory *m_pShapeFactory;
  void setModel();
};

#endif // PAINTER_H
