#include "arc.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

Arc::Arc() {

}

Arc::~Arc() {

}

void Arc::draw(QPaintDevice *device) {
    QPainter painter(device);
    int startAngle = 80 * 16;   //起始角度,角度被分成了十六分之一
    int spanAngle = 120 * 16;   //跨越度数
    painter.drawArc(rect, startAngle, spanAngle);
    painter.end();
}

bool Arc::contains(QPoint &point) {
    region = QRegion(rect, QRegion::Rectangle);
    return region.contains(point);
}

QString Arc::getDllModName() {
    QString name("Arc.dll");
    return name;
}

/***************************************************************
 * 以下导出函数不能作为类的成员
 * *************************************************************/
ARCSHARED_EXPORT Shape* instance() {
    Shape *shape = new Arc;
    return shape;
}

ARCSHARED_EXPORT Shape* getDulShapeInstance(Shape &shape) {
    Shape* arc = new Arc;
    arc->keyPoints = shape.keyPoints;
    return arc;
}
