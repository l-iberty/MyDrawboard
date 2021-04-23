#include "circlepainter.h"

CirclePainter::CirclePainter() {
  m_pShapeFactory = new CircleFactory;
  m_pDrawingShape = m_pShapeFactory->createShape();
}

CirclePainter::~CirclePainter() {}

void CirclePainter::getFactoryFileName(char *pszFileName) {
  if (pszFileName != NULL) {
    strcpy(pszFileName, "CirclePainterFactory.DLL");
  }
}

void CirclePainter::handleMouseMovePoint(QMouseEvent *evt) { handleMousePressPoint(evt->pos()); }

void CirclePainter::handleMousePressPoint(QPoint &point) {
  if (m_pDrawingShape->getKeyPoints().size() < 2) {
    m_pDrawingShape->addKeyPoints(point);
  } else {
    m_pDrawingShape->removeLastKeyPoints();
    m_pDrawingShape->addKeyPoints(point);
  }
}

void CirclePainter::draw(QPaintDevice *device) {
  Painter::setModel();
  QPainter painter(device);
  painter.drawEllipse(m_pDrawingShape->getModel());
  painter.end();
}

void CirclePainter::draw(Shape *shape, QPaintDevice *device) {
  QPainter painter(device);
  painter.drawEllipse(shape->getModel());
  painter.end();
}
