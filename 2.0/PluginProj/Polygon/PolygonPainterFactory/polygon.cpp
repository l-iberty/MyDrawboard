#include "polygon.h"

MyPolygon::MyPolygon() {

}

MyPolygon::~MyPolygon() {

}

void MyPolygon::setKeyPoints(QVector<QPoint> &keyPoints) {
    Shape::setKeyPoints(keyPoints);
    setPolygon(keyPoints);
}

bool MyPolygon::contains(QPoint &point) {
    return m_Polygon.containsPoint(point, Qt::OddEvenFill);
}

void MyPolygon::setPolygon(QVector<QPoint> &points) {
    m_Polygon = QPolygon(points);
}

QPolygon& MyPolygon::getPolygon() {
    return m_Polygon;
}
