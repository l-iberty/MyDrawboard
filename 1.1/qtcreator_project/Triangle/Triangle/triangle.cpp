#include "Triangle.h"


Triangle::Triangle() {

}

Triangle::~Triangle() {

}

void Triangle::setRect() {
    // No need to set rect
}

void Triangle::draw(QPaintDevice *device) {
    triangle = new QPolygon(keyPoints);

    QPainter painter(device);
    painter.drawPolygon(*triangle);
    painter.end();
}

void Triangle::drag(QMouseEvent *evt, QPaintDevice *device) {
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

bool Triangle::contains(QPoint &point) {
    return triangle->containsPoint(point, Qt::OddEvenFill);
}

void Triangle::addKeyPoints(QMouseEvent *evt) {
    QPoint p2 = QPoint();
    QPoint p3 = QPoint();
    int dx;

    if (keyPoints.size() <= 1) {
        keyPoints.push_back(evt->pos());
    }
    else {
        while(keyPoints.size() > 1)
            keyPoints.removeLast();

        p2.setX(evt->pos().rx());
        p2.setY(keyPoints.first().ry());

        dx = abs(p2.rx() - keyPoints.first().rx());

        p3.setX((keyPoints.first().rx() + evt->pos().rx()) / 2);
        p3.setY(keyPoints.first().ry() - dx);

        keyPoints.push_back(p2);
        keyPoints.push_back(p3);
    }
}

void Triangle::addKeyPoints(QPoint &point) {
    keyPoints.push_back(point);
    while (keyPoints.size() > 3)
        keyPoints.removeLast();
}

void Triangle::clearKeyPoints() {
    keyPoints.clear();
}

void Triangle::setP1(QPoint &point) {
    this->p1 = new QPoint(point);
}

void Triangle::setP2(QPoint &point) {
    this->p2 = new QPoint(point);
}

QString Triangle::getDllModName() {
    QString name("Triangle.dll");
    return name;
}


/***************************************************************
 * 以下导出函数不能作为类的成员
 * *************************************************************/
TRIANGLESHARED_EXPORT Shape* instance() {
    Shape *shape = new Triangle;
    return shape;
}

TRIANGLESHARED_EXPORT Shape* getDulShapeInstance(Shape &shape) {
    Shape* triangle = new Triangle;
    triangle->keyPoints = shape.keyPoints;
    return triangle;
}
