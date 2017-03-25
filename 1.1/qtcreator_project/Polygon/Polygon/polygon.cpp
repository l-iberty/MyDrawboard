#include "polygon.h"


Polygon::Polygon() {

}

Polygon::~Polygon() {

}

void Polygon::setRect() {
    // No need to set rect
}

void Polygon::draw(QPaintDevice *device) {
    QPoint NULLPOINT = QPoint(0, 0);
    bool isEqual = ((movingPoint.rx() == NULLPOINT.rx()) &&
                    (movingPoint.ry() == NULLPOINT.ry()));

    if (!isEqual)
        keyPoints.push_back(movingPoint);

    polygon = new QPolygon(keyPoints);

    if (!isEqual)
        keyPoints.removeLast();

    QPainter painter(device);
    painter.drawPolygon(*polygon);
    painter.end();
}

void Polygon::drag(QMouseEvent *evt, QPaintDevice *device) {
    // 取得坐标增量
    int dx = evt->pos().rx() - p1->rx();
    int dy = evt->pos().ry() - p1->ry();

    // 更新关键点
    for (int i = 0;i < keyPoints.size();i++) {
        QPoint point = keyPoints.at(i);
        int newX = point.rx() + dx;
        int newY = point.ry() + dy;
        QPoint newPoint(newX, newY);
        keyPoints.replace(i, newPoint);
    }

    draw(device);
}

bool Polygon::contains(QPoint &point) {
    return polygon->containsPoint(point, Qt::OddEvenFill);
}

void Polygon::addKeyPoints(QMouseEvent *evt) {
    movingPoint = evt->pos();
}

void Polygon::addKeyPoints(QPoint &point) {
    keyPoints.push_back(point);
}

void Polygon::clearKeyPoints() {
    keyPoints.clear();
}

void Polygon::setP1(QPoint &point) {
    this->p1 = new QPoint(point);
}

void Polygon::setP2(QPoint &point) {
    this->p2 = new QPoint(point);
}

QString Polygon::getDllModName() {
    QString name("Polygon.dll");
    return name;
}


/***************************************************************
 * 以下导出函数不能作为类的成员
 * *************************************************************/
POLYGONSHARED_EXPORT Shape* instance() {
    Shape *shape = new Polygon;
    return shape;
}

POLYGONSHARED_EXPORT Shape* getDulShapeInstance(Shape &shape) {
    Shape* polygon = new Polygon;
    polygon->keyPoints = shape.keyPoints;
    return polygon;
}
