#include "rectangle.h"

MyRectangle::MyRectangle() {

}

MyRectangle::~MyRectangle() {

}

bool MyRectangle::contains(QPoint &point) {
   m_Region = QRegion(m_Model, QRegion::Rectangle);
   return m_Region.contains(point);
}
