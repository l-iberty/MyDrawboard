#include "circle.h"
#include <cmath>

Circle::Circle() {

}

Circle::~Circle() {

}

void Circle::draw(QPaintDevice *device) {
    int x1 = keyP1->rx();
    int y1 = keyP1->ry();
    int x2 = keyP2->rx();
    int y2 = keyP2->ry();
    int dx = x2 - x1;
    int dy = y2 - y1;

    centerX = (x1 + x2) / 2;
    centerY = (y1 + y2) / 2;
    QPoint center = QPoint(centerX, centerY);
    r = sqrt(dx * dx + dy * dy) / 2;

    QPainter *qpainter = new QPainter(device);
    qpainter->drawEllipse(center, r, r);
    qpainter->end();
}

void Circle::drag(QMouseEvent *evt, QPaintDevice *device) {
    // 取得坐标增量
    int dx = evt->pos().rx() - p1->rx();
    int dy = evt->pos().ry() - p1->ry();

    // 更新 keyP1
    int newX1 = keyP1->rx() + dx;
    int newY1 = keyP1->ry() + dy;
    delete keyP1;
    keyP1 = new QPoint(newX1, newY1);

    // 更新 keyP2
    int newX2 = keyP2->rx() + dx;
    int newY2 = keyP2->ry() + dy;
    delete keyP2;
    keyP2 = new QPoint(newX2, newY2);

    draw(device);
}

bool Circle::contains(QPoint &point) {
    // 使用 QRegion 构建(椭)圆
    int topleftX = centerX - r;
    int topleftY = centerY - r;
    int bottomrightX = centerX + r;
    int bottomrightY = centerY + r;
    QPoint topleft = QPoint(topleftX, topleftY);
    QPoint bottomright = QPoint(bottomrightX, bottomrightY);
    rect = QRect(topleft, bottomright);
    region = QRegion(rect, QRegion::Ellipse);

    return region.contains(point);

}

void Circle::setKeyP1(QPoint &point) {
    this->keyP1 = new QPoint(point);
}

void Circle::setKeyP2(QPoint &point) {
    this->keyP2 = new QPoint(point);
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
    circle->keyP1 = new QPoint(*shape.keyP1);
    circle->keyP2 = new QPoint(*shape.keyP2);
    return circle;
}
