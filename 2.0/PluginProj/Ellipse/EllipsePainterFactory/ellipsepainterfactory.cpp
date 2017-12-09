#include "ellipsepainterfactory.h"
#include "../../Common/global.h"
#include <string>

EllipsePainterFactory::EllipsePainterFactory() {

}

EllipsePainterFactory::~EllipsePainterFactory() {

}

Painter* EllipsePainterFactory::createPainter() {
    Painter *painter = new EllipsePainter;
    return painter;
}

//////////////////////// exported functions ////////////////////////

DLL_EXPORT void getPluginName(char *pszName) {
    if (pszName != NULL) {
        strcpy(pszName, "Ellipse");
    }
}

DLL_EXPORT PainterFactory* PainterFactoryInstance() {
    PainterFactory* painterFactory = new EllipsePainterFactory;
    return painterFactory;
}
