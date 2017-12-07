#include "shape.h"

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
        QRect rect(m_KeyPoints.first(), m_KeyPoints.last());
		setModel(rect);
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

void Shape::setModel(QRect &model) {
	QPoint pt1 = model.topLeft();
	QPoint pt2 = model.bottomRight();
	QPoint topLeft = (pt1.rx() < pt2.rx()) ? pt1 : pt2;
	QPoint bottomRight = (pt1.rx() > pt2.rx()) ? pt1 : pt2;
    m_Model = QRect(topLeft, bottomRight);
}

QRect& Shape::getModel() {
    return m_Model;
}
