#ifndef PAINTER_H
#define PAINTER_H
#include "shape.h"

// 设计原则:
// Painter 不关心需要绘制的是什么图形, 它只关心 "draw" 这个动作,
// 至于绘制什么图形, 由 Painter::shape->draw(QPaintDevice *) 完成.

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