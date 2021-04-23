#include "squarepainter.h"

SquarePainter::SquarePainter() {
  m_pShapeFactory = new SquareFactory;
  m_pDrawingShape = m_pShapeFactory->createShape();
}

SquarePainter::~SquarePainter() {}

void SquarePainter::getFactoryFileName(char *pszFileName) {
  if (pszFileName != NULL) {
    strcpy(pszFileName, "SquarePainterFactory.DLL");
  }
}

void SquarePainter::handleMouseMovePoint(QMouseEvent *evt) { handleMousePressPoint(evt->pos()); }

void SquarePainter::handleMousePressPoint(QPoint &point) {
  if (m_pDrawingShape->getKeyPoints().size() < 2) {
    m_pDrawingShape->addKeyPoints(point);
  } else {
    m_pDrawingShape->removeLastKeyPoints();
    m_pDrawingShape->addKeyPoints(point);
  }
}

void SquarePainter::draw(QPaintDevice *device) {
  Painter::setModel();
  QPainter painter(device);
  painter.drawRect(m_pDrawingShape->getModel());
  painter.end();
}

void SquarePainter::draw(Shape *shape, QPaintDevice *device) {
  QPainter painter(device);
  painter.drawRect(shape->getModel());
  painter.end();
}
