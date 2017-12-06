#include "ellipsepainter.h"

EllipsePainter::EllipsePainter() {
    m_pShapeFactory = new EllipseFactory;
    m_pDrawingShape = m_pShapeFactory->createShape();
}

EllipsePainter::~EllipsePainter() {

}

void EllipsePainter::getFactoryFileName(char *pszFileName) {
    if (pszFileName != NULL) {
        strcpy(pszFileName, "EllipsePainterFactory.DLL");
    }
}

void EllipsePainter::handleMouseMovePoint(QMouseEvent *evt) {
    handleMousePressPoint(evt->pos());
}

void EllipsePainter::handleMousePressPoint(QPoint &point) {
   if (m_pDrawingShape->getKeyPoints().size() < 2) {
       m_pDrawingShape->addKeyPoints(point);
   }
   else {
       m_pDrawingShape->removeLastKeyPoints();
       m_pDrawingShape->addKeyPoints(point);
   }
}

void EllipsePainter::draw(QPaintDevice *device) {
    Painter::setModel();
    QPainter painter(device);
    painter.drawEllipse(m_pDrawingShape->getModel());
    painter.end();
}

void EllipsePainter::draw(Shape *shape, QPaintDevice *device) {
    QPainter painter(device);
    painter.drawEllipse(shape->getModel());
    painter.end();
}

