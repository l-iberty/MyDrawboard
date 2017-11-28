#include "polygon.h"


Polygon::Polygon() {

}

Polygon::~Polygon() {

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

bool Polygon::contains(QPoint &point) {
    return polygon->containsPoint(point, Qt::OddEvenFill);
}

void Polygon::addKeyPoints(QMouseEvent *evt) {
    movingPoint = evt->pos();
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
