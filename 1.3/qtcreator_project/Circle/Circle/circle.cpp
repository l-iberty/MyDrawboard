#include "circle.h"
#include <cmath>

Circle::Circle() {

}

Circle::~Circle() {

}

void Circle::setRect(QRect &rect) {
    int x1 = rect.topLeft().rx();
    int x2 = rect.bottomRight().rx();
    int y1 = rect.topLeft().ry();
    int y2 = rect.bottomRight().ry();
    int dx = x2 - x1;
    int dy = y2 - y1;
    centerX = (x1 + x2) / 2;
    centerY = (y1 + y2) / 2;
    r = sqrt(dx * dx + dy * dy);

    int topLX = centerX - r;
    int topLY = centerY - r;
    int bottomRX = centerX + r;
    int bottomRY = centerY + r;
    QPoint topLeft = QPoint(topLX, topLY);
    QPoint bottomRight = QPoint(bottomRX, bottomRY);

    this->rect.setTopLeft(topLeft);
    this->rect.setBottomRight(bottomRight);
}

void Circle::draw(QPaintDevice *device) {
    QPainter painter(device);
    painter.drawEllipse(rect);
    painter.end();
}

bool Circle::contains(QPoint &point) {
    region = QRegion(rect, QRegion::Ellipse);
    return region.contains(point);
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
