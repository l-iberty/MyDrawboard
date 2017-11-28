#include "Triangle.h"


Triangle::Triangle() {

}

Triangle::~Triangle() {

}

void Triangle::draw(QPaintDevice *device) {
    triangle = new QPolygon(keyPoints);
    QPainter painter(device);
    painter.drawPolygon(*triangle);
    painter.end();
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
