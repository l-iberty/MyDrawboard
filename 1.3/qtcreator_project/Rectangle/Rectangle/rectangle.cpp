#include "rectangle.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

Rectangle::Rectangle() {

}

Rectangle::~Rectangle() {

}

void Rectangle::draw(QPaintDevice *device) {
    QPainter painter(device);
    painter.drawRect(rect);
    painter.end();
}

bool Rectangle::contains(QPoint &point) {
    region = QRegion(rect, QRegion::Rectangle);
    return region.contains(point);
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
    rectangle->keyPoints = shape.keyPoints;
    return rectangle;
}
