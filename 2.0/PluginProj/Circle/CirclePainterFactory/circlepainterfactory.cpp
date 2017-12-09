#include "circlepainterfactory.h"
#include "../../Common/global.h"
#include <string>

CirclePainterFactory::CirclePainterFactory() {

}

CirclePainterFactory::~CirclePainterFactory() {

}

Painter* CirclePainterFactory::createPainter() {
    Painter *painter = new CirclePainter;
    return painter;
}

//////////////////////// exported functions ////////////////////////

DLL_EXPORT void getPluginName(char *pszName) {
    if (pszName != NULL) {
        strcpy(pszName, "Circle");
    }
}

DLL_EXPORT PainterFactory* PainterFactoryInstance() {
    PainterFactory* painterFactory = new CirclePainterFactory;
    return painterFactory;
}
