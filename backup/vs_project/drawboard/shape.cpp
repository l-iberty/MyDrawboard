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
}

void Shape::updateKeyPoints(int index, QPoint &point) {
	m_KeyPoints.replace(index, point);
}

void Shape::removeLastKeyPoints() {
	m_KeyPoints.removeLast();
}

void Shape::addKeyPoints(QMouseEvent *evt) {
    if (m_KeyPoints.size() <= 1) {
        addKeyPoints(evt->pos());
    }
    else {
        removeLastKeyPoints();
        addKeyPoints(evt->pos());
    }
}

void Shape::addKeyPoints(QPoint &point) {
	m_KeyPoints.push_back(point);
}

void Shape::clearKeyPoints() {
	m_KeyPoints.clear();
}

void Shape::setModel(QRect &model) {
    m_Model.setTopLeft(model.topLeft());
	m_Model.setBottomRight(model.bottomRight());
}
