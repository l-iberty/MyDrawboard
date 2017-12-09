#include "squarepainterfactory.h"
#include "../../Common/global.h"
#include <string>

SquarePainterFactory::SquarePainterFactory() {

}

SquarePainterFactory::~SquarePainterFactory() {

}

Painter* SquarePainterFactory::createPainter() {
    Painter *painter = new SquarePainter;
    return painter;
}

//////////////////////// exported functions ////////////////////////

DLL_EXPORT void getPluginName(char *pszName) {
    if (pszName != NULL) {
        strcpy(pszName, "Square");
    }
}

DLL_EXPORT PainterFactory* PainterFactoryInstance() {
    PainterFactory* painterFactory = new SquarePainterFactory;
    return painterFactory;
}
