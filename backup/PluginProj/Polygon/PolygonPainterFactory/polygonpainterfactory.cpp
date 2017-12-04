#include "polygonpainterfactory.h"
#include "../../Common/global.h"

PolygonPainterFactory::PolygonPainterFactory() {

}

PolygonPainterFactory::~PolygonPainterFactory() {

}

Painter* PolygonPainterFactory::createPainter() {
    Painter* painter = new PolygonPainter;
    return painter;
}

DLL_EXPORT PainterFactory* PainterFactoryInstance() {
    PainterFactory* painterFactory = new PolygonPainterFactory;
    return painterFactory;
}
