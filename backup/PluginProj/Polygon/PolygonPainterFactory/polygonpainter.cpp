#include "polygonpainter.h"
#include <string>

PolygonPainter::PolygonPainter() {
    m_pShapeFactory = new PolygonFactory;
    m_pDrawingShape = m_pShapeFactory->createShape();
    m_MovingPoint = QPoint(0, 0);
}

PolygonPainter::~PolygonPainter() {

}

void PolygonPainter::getFactoryFileName(char *pszFileName) {
    if (pszFileName != NULL) {
        strcpy(pszFileName, "PolygonPainterFactory.DLL");
    }
}

void PolygonPainter::handleMouseMovePoint(QMouseEvent *evt) {
    m_MovingPoint = evt->pos();
}

void PolygonPainter::handleMousePressPoint(QPoint &point) {
   m_pDrawingShape->addKeyPoints(point);
}

void PolygonPainter::draw(QPaintDevice *device) {
    QPoint NULLPOINT = QPoint(0, 0);
    bool isEqual = ((m_MovingPoint.rx() == NULLPOINT.rx()) &&
                    (m_MovingPoint.ry() == NULLPOINT.ry()));

    if (!isEqual)
        m_pDrawingShape->addKeyPoints(m_MovingPoint);

    setPolygon(m_pDrawingShape->getKeyPoints());

    if (!isEqual)
        m_pDrawingShape->removeLastKeyPoints();

    QPainter painter(device);
    painter.drawPolygon(m_Polygon);
    painter.end();
}

void PolygonPainter::draw(Shape *shape, QPaintDevice *device) {
    QPolygon polygon(shape->getKeyPoints());
    QPainter painter(device);
    painter.drawPolygon(polygon);
    painter.end();
}
