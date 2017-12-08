#include "shape.h"

#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

Shape::Shape() {

}

Shape::~Shape() {

}

QVector<QPoint>& Shape::getKeyPoints() {
    return m_KeyPoints;
}

void Shape::setKeyPoints(QVector<QPoint> &keyPoints) {
    m_KeyPoints = keyPoints;
    if (m_KeyPoints.size() == 2) {
        setModel(m_KeyPoints.first(), m_KeyPoints.last());
    }
}

void Shape::updateKeyPoints(int index, QPoint &point) {
	m_KeyPoints.replace(index, point);
}

void Shape::removeLastKeyPoints() {
	m_KeyPoints.removeLast();
}

void Shape::addKeyPoints(QMouseEvent *evt) {
    addKeyPoints(evt->pos());
}

void Shape::addKeyPoints(QPoint &point) {
	m_KeyPoints.push_back(point);
}

void Shape::clearKeyPoints() {
	m_KeyPoints.clear();
}

void Shape::setModel(QPoint &pt1, QPoint &pt2) {
    int topLeft_x = min(pt1.rx(), pt2.rx());
    int topLeft_y = min(pt1.ry(), pt2.ry());
    int bottomRight_x = max(pt1.rx(), pt2.rx());
    int bottomRight_y = max(pt1.ry(), pt2.ry());

    QPoint topLeft(topLeft_x, topLeft_y);
    QPoint bottomRight(bottomRight_x, bottomRight_y);
    m_Model = QRect(topLeft, bottomRight);
}

QRect& Shape::getModel() {
    return m_Model;
}
