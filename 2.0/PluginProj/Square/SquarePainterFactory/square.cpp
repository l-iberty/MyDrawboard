#include "square.h"
#include <math.h>

MySquare::MySquare() {

}

MySquare::~MySquare() {

}

bool MySquare::contains(QPoint &point) {
   m_Region = QRegion(m_Model, QRegion::Rectangle);
   return m_Region.contains(point);
}

void MySquare::setModel(QPoint &pt1, QPoint &pt2) {
    int center_x = (pt1.rx() + pt2.rx()) / 2;
    int center_y = (pt1.ry() + pt2.ry()) / 2;
    int dx = pt2.rx() - pt1.rx();
    int dy = pt2.ry() - pt1.ry();
    int r = sqrt(dx * dx + dy * dy) / 2;
    int topLeft_x = center_x - r;
    int topLeft_y = center_y - r;
    int bottomRight_x = center_x + r;
    int bottomRight_y = center_y + r;

    QPoint topLeft(topLeft_x, topLeft_y);
    QPoint bottomRight(bottomRight_x, bottomRight_y);
    m_Model = QRect(topLeft, bottomRight);
}
