#ifndef PAINTER_FACTORY_H
#define PAINTER_FACTORY_H

#include "painter.h"

class PainterFactory {
public:
	PainterFactory();
	~PainterFactory();
	Painter* createPainter();
};

#endif // PAINTER_FACTORY_H
