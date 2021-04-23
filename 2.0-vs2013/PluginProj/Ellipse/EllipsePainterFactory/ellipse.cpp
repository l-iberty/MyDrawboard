#include "ellipse.h"

MyEllipse::MyEllipse() {}

MyEllipse::~MyEllipse() {}

bool MyEllipse::contains(QPoint &point) {
  m_Region = QRegion(m_Model, QRegion::Ellipse);
  return m_Region.contains(point);
}
