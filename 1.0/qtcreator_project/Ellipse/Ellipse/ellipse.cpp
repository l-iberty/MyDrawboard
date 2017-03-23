#include "ellipse.h"
#include <cmath>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

Ellipse::Ellipse() {

}

Ellipse::~Ellipse() {

}

void Ellipse::draw(QPaintDevice *device) {
    int x1 = keyP1->rx();
    int y1 = keyP1->ry();
    int x2 = keyP2->rx();
    int y2 = keyP2->ry();
    QPoint topLeft = QPoint(x1, y1);
    QPoint bottomRight = QPoint(x2, y2);
    QRect rect = QRect(topLeft, bottomRight);

    QPainter *qpainter = new QPainter(device);
    qpainter->drawEllipse(rect);
    qpainter->end();
}

void Ellipse::drag(QMouseEvent *evt, QPaintDevice *device) {
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

bool Ellipse::contains(QPoint &point) {
    // 使用 QRegion 构建椭圆
    int x1 = keyP1->rx();
    int y1 = keyP1->ry();
    int x2 = keyP2->rx();
    int y2 = keyP2->ry();
    int topleftX = min(x1,x2);
    int topleftY = min(y1,y2);
    int bottomrightX = max(x1,x2);
    int bottomrightY = max(y1,y2);
    QPoint topleft = QPoint(topleftX, topleftY);
    QPoint bottomright = QPoint(bottomrightX, bottomrightY);
    rect = QRect(topleft, bottomright);
    region = QRegion(rect, QRegion::Ellipse);

    return region.contains(point);
}

void Ellipse::setKeyP1(QPoint &point) {
    this->keyP1 = new QPoint(point);
}

void Ellipse::setKeyP2(QPoint &point) {
    this->keyP2 = new QPoint(point);
}

void Ellipse::setP1(QPoint &point) {
    this->p1 = new QPoint(point);
}

void Ellipse::setP2(QPoint &point) {
    this->p2 = new QPoint(point);
}

QString Ellipse::getDllModName() {
    QString name("Ellipse.dll");
    return name;
}

/***************************************************************
 * 以下导出函数不能作为类的成员
 * *************************************************************/
ELLIPSESHARED_EXPORT Shape* instance() {
    Shape *shape = new Ellipse;
    return shape;
}

ELLIPSESHARED_EXPORT Shape* getDulShapeInstance(Shape &shape) {
    Shape* ellipse = new Ellipse;
    ellipse->keyP1 = new QPoint(*shape.keyP1);
    ellipse->keyP2 = new QPoint(*shape.keyP2);
    return ellipse;
}
