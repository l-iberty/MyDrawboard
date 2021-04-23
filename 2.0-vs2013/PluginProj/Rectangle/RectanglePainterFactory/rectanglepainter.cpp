#include "rectanglepainter.h"

RectanglePainter::RectanglePainter() {
  m_pShapeFactory = new RectangleFactory;
  m_pDrawingShape = m_pShapeFactory->createShape();
}

RectanglePainter::~RectanglePainter() {}

void RectanglePainter::getFactoryFileName(char *pszFileName) {
  if (pszFileName != NULL) {
    strcpy(pszFileName, "RectanglePainterFactory.DLL");
  }
}

void RectanglePainter::handleMouseMovePoint(QMouseEvent *evt) { handleMousePressPoint(evt->pos()); }

void RectanglePainter::handleMousePressPoint(QPoint &point) {
  if (m_pDrawingShape->getKeyPoints().size() < 2) {
    m_pDrawingShape->addKeyPoints(point);
  } else {
    m_pDrawingShape->removeLastKeyPoints();
    m_pDrawingShape->addKeyPoints(point);
  }
}

void RectanglePainter::draw(QPaintDevice *device) {
  Painter::setModel();
  QPainter painter(device);
  painter.drawRect(m_pDrawingShape->getModel());
  painter.end();
}

void RectanglePainter::draw(Shape *shape, QPaintDevice *device) {
  QPainter painter(device);
  painter.drawRect(shape->getModel());
  painter.end();
}
