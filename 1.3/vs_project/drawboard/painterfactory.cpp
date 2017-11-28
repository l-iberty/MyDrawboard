#include "painterfactory.h"

PainterFactory::PainterFactory() {

}

PainterFactory::~PainterFactory() {

}

Painter* PainterFactory::createPainter() {
	Painter *painter = new Painter();
	return painter;
}