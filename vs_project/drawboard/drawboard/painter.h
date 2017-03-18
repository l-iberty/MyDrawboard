#ifndef PAINTER_H
#define PAINTER_H
#include "shape.h"

// ���ԭ��:
// Painter ��������Ҫ���Ƶ���ʲôͼ��, ��ֻ���� "draw" �������,
// ���ڻ���ʲôͼ��, �� Painter::shape->draw(QPaintDevice *) ���.

class Painter {
private:
	Shape *shape;
public:
	Painter(Shape *shape);
	~Painter();
	void draw(QPaintDevice *device);
	void drag(QMouseEvent *evt, QPaintDevice *device);
};

#endif // PAINTER_H