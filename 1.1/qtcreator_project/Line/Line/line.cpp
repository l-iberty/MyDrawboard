#include "line.h"
#include <cmath>

Line::Line() {

}

Line::~Line() {

}

void Line::setRect() {
    // No need to set rect
}

void Line::draw(QPaintDevice *device) {
    QPoint keyPoint1 = keyPoints.first();
    QPoint keyPoint2 = keyPoints.last();

    QPainter painter(device);
    painter.drawLine(keyPoint1, keyPoint2);
    painter.end();
}

void Line::drag(QMouseEvent *evt, QPaintDevice *device) {
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

bool Line::contains(QPoint &point) {
    int x0 = point.rx();
    int y0 = point.ry();

    LINEARGS args;
    getArgs(&args);

    double d = abs(args.A * x0 + args.B * y0 + args.C);
    d = d / (sqrt(args.A * args.A + args.B * args.B));

    return (d <= 5.0); // 单位: 像素
}

void Line::addKeyPoints(QMouseEvent *evt) {
    if (keyPoints.size() <= 1) {
        keyPoints.push_back(evt->pos());
    }
    else {
        keyPoints.removeLast();
        keyPoints.push_back(evt->pos());
    }
}

void Line::addKeyPoints(QPoint &point) {
    keyPoints.push_back(point);
}

void Line::clearKeyPoints() {
    keyPoints.clear();
}

void Line::setP1(QPoint &point) {
    this->p1 = new QPoint(point);
}

void Line::setP2(QPoint &point) {
    this->p2 = new QPoint(point);
}

QString Line::getDllModName() {
    QString name("Line.dll");
    return name;
}

void Line::getArgs(PLINEARGS pArgs) {
    QPoint keyPoint1 = keyPoints.first();
    QPoint keyPoint2 = keyPoints.last();

    int x1 = keyPoint1.rx();
    int y1 = keyPoint1.ry();
    int x2 = keyPoint2.rx();
    int y2 = keyPoint2.ry();

    // 根据点斜式得出直线方程的参数
    double k = (y2 - y1) / (x2 - x1);
    pArgs->A = k;
    pArgs->B = -1;
    pArgs->C = y1 - k * x1;
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
    line->keyPoints = shape.keyPoints;
    return line;
}
