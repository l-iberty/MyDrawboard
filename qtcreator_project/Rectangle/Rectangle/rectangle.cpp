#include "rectangle.h"
#include <cmath>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

Rectangle::Rectangle() {

}

Rectangle::~Rectangle() {

}

void Rectangle::draw(QPaintDevice *device) {
    int topleftX = min(keyP1->rx(), keyP2->rx());
    int topleftY = min(keyP1->ry(), keyP2->ry());
    int w = abs(keyP1->rx() - keyP2->rx());
    int h = abs(keyP1->ry() - keyP2->ry());

    QPainter *qpainter = new QPainter(device);
    qpainter->drawRect(topleftX, topleftY, w, h);
    qpainter->end();
}

void Rectangle::drag(QMouseEvent *evt, QPaintDevice *device) {
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

bool Rectangle::contains(QPoint &point) {
    int topleftX = min(keyP1->rx(), keyP2->rx());
    int topleftY = min(keyP1->ry(), keyP2->ry());
    int bottomrightX = max(keyP1->rx(), keyP2->rx());
    int bottomrightY = max(keyP1->ry(), keyP2->ry());
    QPoint topleft = QPoint(topleftX, topleftY);
    QPoint bottomright = QPoint(bottomrightX, bottomrightY);
    rect = QRect(topleft, bottomright);

    region = QRegion(rect, QRegion::Rectangle);
    return region.contains(point);
}

void Rectangle::setKeyP1(QPoint &point) {
    this->keyP1 = new QPoint(point);
}

void Rectangle::setKeyP2(QPoint &point) {
    this->keyP2 = new QPoint(point);
}

void Rectangle::setP1(QPoint &point) {
    this->p1 = new QPoint(point);
}

void Rectangle::setP2(QPoint &point) {
    this->p2 = new QPoint(point);
}

QString Rectangle::getDllModName() {
    QString name("Rectangle.dll");
    return name;
}

/***************************************************************
 * 以下导出函数不能作为类的成员
 * *************************************************************/
RECTANGLESHARED_EXPORT Shape* instance() {
    Shape *shape = new Rectangle;
    return shape;
}

RECTANGLESHARED_EXPORT Shape* getDulShapeInstance(Shape &shape) {
    Shape* rectangle = new Rectangle;
    rectangle->keyP1 = new QPoint(*shape.keyP1);
    rectangle->keyP2 = new QPoint(*shape.keyP2);
    return rectangle;
}
