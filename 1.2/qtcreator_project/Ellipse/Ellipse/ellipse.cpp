#include "ellipse.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

Ellipse::Ellipse() {

}

Ellipse::~Ellipse() {

}

void Ellipse::setRect() {
    QPoint keyPoint1 = keyPoints.first();
    QPoint keyPoint2 = keyPoints.last();

    int x1 = keyPoint1.rx();
    int y1 = keyPoint1.ry();
    int x2 = keyPoint2.rx();
    int y2 = keyPoint2.ry();

    int topLX = min(x1, x2);
    int topLY = min(y1, y2);
    int bottomRX = max(x1, x2);
    int bottomRY = max(y1, y2);

    QPoint topLeft = QPoint(topLX, topLY);
    QPoint bottomRight = QPoint(bottomRX, bottomRY);
    rect = QRect(topLeft, bottomRight);
}

void Ellipse::draw(QPaintDevice *device) {
    setRect();

    QPainter painter(device);
    painter.drawEllipse(rect);
    painter.end();
}

void Ellipse::drag(QMouseEvent *evt, QPaintDevice *device) {
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

bool Ellipse::contains(QPoint &point) {
    setRect();
    region = QRegion(rect, QRegion::Ellipse);

    return region.contains(point);
}

void Ellipse::addKeyPoints(QMouseEvent *evt) {
    if (keyPoints.size() <= 1) {
        keyPoints.push_back(evt->pos());
    }
    else {
        keyPoints.removeLast();
        keyPoints.push_back(evt->pos());
    }
}

void Ellipse::addKeyPoints(QPoint &point) {
    keyPoints.push_back(point);
}

void Ellipse::clearKeyPoints() {
    keyPoints.clear();
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
    ellipse->keyPoints = shape.keyPoints;
    return ellipse;
}
