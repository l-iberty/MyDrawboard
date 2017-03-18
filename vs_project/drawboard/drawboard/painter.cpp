#include "painter.h"

Painter::Painter(Shape *shape) {
	this->shape = shape;
}

void Painter::draw(QPaintDevice *device) {
	this->shape->draw(device);
}

void Painter::drag(QMouseEvent *evt, QPaintDevice *device) {
	this->shape->drag(evt, device);
}

Painter::~Painter() {
	delete this->shape;
}