#include "painter.h"

Painter::Painter() {
    m_pDrawingShape = NULL;
    m_pDraggingShape = NULL;
    m_pShapeFactory = NULL;
}

Painter::~Painter() {
    if (m_pDrawingShape != NULL) { delete m_pDrawingShape; }
    if (m_pShapeFactory != NULL) { delete m_pShapeFactory; }
    for (int i = 0;i < m_ShapeList.size();i++) {
        if (m_ShapeList.at(i) != NULL) {
            delete m_ShapeList.at(i);
        }
    }
}

void Painter::drag(QPaintDevice *device) {
    int dx = m_EndPoint.rx() - m_StartPoint.rx();
    int dy = m_EndPoint.ry() - m_StartPoint.ry();
    QVector<QPoint> points = m_pDraggingShape->getKeyPoints();

    for (int i = 0;i < points.size();i++) {
        QPoint point = points.at(i);
        int x = point.rx() + dx;
        int y = point.ry() + dy;
        point = QPoint(x, y);
        points.replace(i, point);
    }
    m_pDraggingShape->setKeyPoints(points);
    draw(m_pDraggingShape, device);
}

Shape* Painter::find(QPoint &point) {
    Shape *shape = NULL;
    for (int i = 0;i < m_ShapeList.size();i++) {
        if (m_ShapeList.at(i)->contains(point)) {
            shape = m_ShapeList.at(i);
            break;
        }
    }
    return shape;
}

void Painter::save() {
    if (m_pDrawingShape != NULL) {
        Shape *shapeCpy = m_pShapeFactory->createShape(m_pDrawingShape);
        m_ShapeList.push_back(shapeCpy);
        delete m_pDrawingShape; // destory the old one
        m_pDrawingShape = m_pShapeFactory->createShape(); // create a new one
        //m_ShapeList.push_back(m_pDrawingShape);
        //m_pDrawingShape = m_pShapeFactory->createShape();
    }
}

void Painter::setDrawingShape(QVector<QPoint> &keyPoints) {
    if (m_pDrawingShape != NULL) {
        m_pDrawingShape->setKeyPoints(keyPoints);
    }
}

void Painter::setDraggingShape(Shape *shape) {
    m_pDraggingShape = shape;
}

void Painter::setModel() {
    if (m_pDrawingShape->getKeyPoints().size() == 2) {
        QPoint pt1 = m_pDrawingShape->getKeyPoints().first();
        QPoint pt2 = m_pDrawingShape->getKeyPoints().last();
        m_pDrawingShape->setModel(pt1, pt2);
    }
}

void Painter::setStartPoint(QPoint &point) {
    m_StartPoint = QPoint(point.rx(), point.ry());
}

void Painter::setEndPoint(QPoint &point) {
    m_EndPoint = QPoint(point.rx(), point.ry());
}

QPoint& Painter::getStartPoint() {
    return m_StartPoint;
}

QPoint& Painter::getEndPoint() {
    return m_EndPoint;
}

QList<Shape*>& Painter::getShapeList() {
    return m_ShapeList;
}

Shape* Painter::getShapeListItem(int i) {
    return m_ShapeList.at(i);
}

bool Painter::isEmptyShapeList() {
    return m_ShapeList.isEmpty();
}

void Painter::clearShapeList() {
    for (int i = 0;i < m_ShapeList.size();i++) {
        delete m_ShapeList.at(i);
    }
    m_ShapeList.clear();
}

void Painter::drawAllShapes(QPaintDevice *device) {
    for (int i = 0;i < m_ShapeList.size();i++) {
        draw(m_ShapeList.at(i), device);
    }
}
