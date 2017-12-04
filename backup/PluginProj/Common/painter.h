#ifndef PAINTER_H
#define PAINTER_H

#include "shape.h"
#include "shapefactory.h"
#include <QtCore/QList>

class Painter {
public:
    Painter();
    virtual ~Painter();
    virtual void handleMouseMovePoint(QMouseEvent *evt);
    virtual void handleMousePressPoint(QPoint &point);
    virtual void draw(QPaintDevice *device) = 0;
    virtual void draw(Shape *shape, QPaintDevice *device) = 0;
    virtual void drag(QPaintDevice *device);
    virtual Shape* find(QPoint &point);
    virtual void save();
    void setDraggingShape(Shape *shape);
    void setStartPoint(QPoint &point);
    void setEndPoint(QPoint &point);
    QPoint& getStartPoint();
    QPoint& getEndPoint();
    Shape* getShapeListItem(int i);
    bool isEmptyShapeList();
    void clearShapeList();
    void drawAllShapes(QPaintDevice *device);
protected:
	Shape *m_pDrawingShape;
	Shape *m_pDraggingShape;
	QPoint m_StartPoint, m_EndPoint;
	QList<Shape*> m_ShapeList;
	ShapeFactory *m_pShapeFactory;
private:
    void setModel();
};

#endif // PAINTER_H
