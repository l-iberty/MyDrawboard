#include "ellipse.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

Ellipse::Ellipse() {

}

Ellipse::~Ellipse() {

}

void Ellipse::draw(QPaintDevice *device) {
    QPainter painter(device);
    painter.drawEllipse(rect);
    painter.end();
}

bool Ellipse::contains(QPoint &point) {
    region = QRegion(rect, QRegion::Ellipse);
    return region.contains(point);
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
    ellipse->keyPoints = shape.keyPoints;
    return ellipse;
}
