#ifndef PAINTER_H
#define PAINTER_H

#include "shape.h"

class Painter {
public:
	Painter();
	~Painter();
	void draw(Shape *shape, QPaintDevice *device);
	void drag(Shape *shape, QMouseEvent *evt, QPaintDevice *device);
private:
	void setRect(Shape *shape);
};

#endif // PAINTER_H
