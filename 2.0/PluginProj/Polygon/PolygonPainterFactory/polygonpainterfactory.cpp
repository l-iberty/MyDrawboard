#include "polygonpainterfactory.h"
#include "../../Common/global.h"
#include <string>

PolygonPainterFactory::PolygonPainterFactory() {

}

PolygonPainterFactory::~PolygonPainterFactory() {

}

Painter* PolygonPainterFactory::createPainter() {
    Painter* painter = new PolygonPainter;
    return painter;
}

//////////////////////// exported functions ////////////////////////

DLL_EXPORT void getPluginName(char *pszName) {
    if (pszName != NULL) {
        strcpy(pszName, "Polygon");
    }
}

DLL_EXPORT PainterFactory* PainterFactoryInstance() {
    PainterFactory* painterFactory = new PolygonPainterFactory;
    return painterFactory;
}
