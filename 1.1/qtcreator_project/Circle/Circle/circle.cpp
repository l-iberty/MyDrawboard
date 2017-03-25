#include "circle.h"
#include <cmath>

Circle::Circle() {

}

Circle::~Circle() {

}

void Circle::setRect() {
    QPoint keyPoint1 = keyPoints.first();
    QPoint keyPoint2 = keyPoints.last();

    int x1 = keyPoint1.rx();
    int y1 = keyPoint1.ry();
    int x2 = keyPoint2.rx();
    int y2 = keyPoint2.ry();
    int dx = x2 - x1;
    int dy = y2 - y1;

    centerX = (x1 + x2) / 2;
    centerY = (y1 + y2) / 2;
    r = sqrt(dx * dx + dy * dy) / 2;

    int topLX = centerX - r;
    int topLY = centerY - r;
    int bottomRX = centerX + r;
    int bottomRY = centerY + r;
    QPoint topLeft = QPoint(topLX, topLY);
    QPoint bottomRight = QPoint(bottomRX, bottomRY);

    rect = QRect(topLeft, bottomRight);
}

void Circle::draw(QPaintDevice *device) {
    setRect();

    QPainter painter(device);
    painter.drawEllipse(rect);
    painter.end();
}

void Circle::drag(QMouseEvent *evt, QPaintDevice *device) {
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

bool Circle::contains(QPoint &point) {
    setRect();
    region = QRegion(rect, QRegion::Ellipse);

    return region.contains(point);

}

void Circle::addKeyPoints(QMouseEvent *evt) {
    if (keyPoints.size() <= 1) {
        keyPoints.push_back(evt->pos());
    }
    else {
        keyPoints.removeLast();
        keyPoints.push_back(evt->pos());
    }
}

void Circle::addKeyPoints(QPoint &point) {
    keyPoints.push_back(point);
}

void Circle::clearKeyPoints() {
    keyPoints.clear();
}

void Circle::setP1(QPoint &point) {
    this->p1 = new QPoint(point);
}

void Circle::setP2(QPoint &point) {
    this->p2 = new QPoint(point);
}

QString Circle::getDllModName() {
    QString name("Circle.dll");
    return name;
}


/***************************************************************
 * 以下导出函数不能作为类的成员
 * *************************************************************/
CIRCLESHARED_EXPORT Shape* instance() {
    Shape *shape = new Circle;
    return shape;
}

CIRCLESHARED_EXPORT Shape* getDulShapeInstance(Shape &shape) {
    Shape* circle = new Circle;
    circle->keyPoints = shape.keyPoints;
    return circle;
}
