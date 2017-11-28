#include "painter.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

Painter::Painter() {

}

Painter::~Painter() {

}

void Painter::draw(Shape *shape, QPaintDevice *device) {
	setRect(shape);
	shape->draw(device);
}

void Painter::drag(Shape *shape, QMouseEvent *evt, QPaintDevice *device) {
	// 取得坐标增量
	int dx = evt->pos().rx() - shape->getP1()->rx();
	int dy = evt->pos().ry() - shape->getP1()->ry();

	// 更新关键点
	for (int i = 0;i < shape->keyPoints.size();i++) {
		QPoint point = shape->keyPoints.at(i);
		int newX = point.rx() + dx;
		int newY = point.ry() + dy;
		QPoint newPoint(newX, newY);
		shape->keyPoints.replace(i, newPoint);
	}
	draw(shape, device);
}

void Painter::setRect(Shape *shape) {
	QPoint keyPoint1 = shape->keyPoints.first();
	QPoint keyPoint2 = shape->keyPoints.last();

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
	QRect rect = QRect(topLeft, bottomRight);
	shape->setRect(rect);
}
