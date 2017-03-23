#include "line.h"
#include <cmath>

Line::Line() {

}

Line::~Line() {

}

void Line::draw(QPaintDevice *device) {
    QPainter *qpainter = new QPainter(device);
    qpainter->drawLine(*keyP1, *keyP2);
    qpainter->end();
}

void Line::drag(QMouseEvent *evt, QPaintDevice *device) {
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

bool Line::contains(QPoint &point) {
    int x0 = point.rx();
    int y0 = point.ry();

    LINEARGS args;
    getArgs(&args);

    double d = abs(args.A * x0 + args.B * y0 + args.C);
    d = d / (sqrt(args.A * args.A + args.B * args.B));

    return (d <= 5.0); // 单位: 像素
}

void Line::setKeyP1(QPoint &point) {
    this->keyP1 = new QPoint(point);
}

void Line::setKeyP2(QPoint &point) {
    this->keyP2 = new QPoint(point);
}

void Line::setP1(QPoint &point) {
    this->p1 = new QPoint(point);
}

void Line::setP2(QPoint &point) {
    this->p2 = new QPoint(point);
}

void Line::getArgs(PLINEARGS pArgs) {
    int x1 = keyP1->rx();
    int y1 = keyP1->ry();
    int x2 = keyP2->rx();
    int y2 = keyP2->ry();

    // 根据点斜式得出直线方程的参数
    double k = (y2 - y1) / (x2 - x1);
    pArgs->A = k;
    pArgs->B = -1;
    pArgs->C = y1 - k * x1;
}

QString Line::getDllModName() {
    QString name("Line.dll");
    return name;
}

/***************************************************************
 * 以下导出函数不能作为类的成员
 * *************************************************************/
LINESHARED_EXPORT Shape* instance() {
    Shape *shape = new Line;
    return shape;
}

LINESHARED_EXPORT Shape* getDulShapeInstance(Shape &shape) {
    Shape* line = new Line;
    line->keyP1 = new QPoint(*shape.keyP1);
    line->keyP2 = new QPoint(*shape.keyP2);
    return line;
}
