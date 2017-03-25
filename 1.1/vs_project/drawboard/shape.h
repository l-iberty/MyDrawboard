#ifndef SHAPE_H
#define SHAPE_H
#include <QtGui/QPainter>
#include <QtGui/QtEvents>

class Shape {
protected:
	QRegion region;
	QRect rect;
	QPoint *p1, *p2; // ������קģʽ

public:
	QVector<QPoint> keyPoints; // ����ͼ��λ�õĹؼ���

	virtual void setRect() = 0;
	virtual void draw(QPaintDevice *device) = 0; // device ָ����Ҫ���ĸ��豸(����)�Ͻ��л���
	virtual void drag(QMouseEvent *evt, QPaintDevice *device) = 0;
	virtual bool contains(QPoint &point) = 0;
	virtual void addKeyPoints(QMouseEvent *evt) = 0;
	virtual void addKeyPoints(QPoint &point) = 0;
	virtual void clearKeyPoints() = 0;
	virtual void setP1(QPoint &point) = 0;
	virtual void setP2(QPoint &point) = 0;
	virtual QString getDllModName() = 0;
};

#endif // SHAPE_H
