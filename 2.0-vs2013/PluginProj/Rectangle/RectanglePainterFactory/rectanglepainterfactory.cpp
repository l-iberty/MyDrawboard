#include "rectanglepainterfactory.h"
#include "../../Common/global.h"
#include <string>

RectanglePainterFactory::RectanglePainterFactory() {}

RectanglePainterFactory::~RectanglePainterFactory() {}

Painter *RectanglePainterFactory::createPainter() {
  Painter *painter = new RectanglePainter;
  return painter;
}

//////////////////////// exported functions ////////////////////////

DLL_EXPORT void getPluginName(char *pszName) {
  if (pszName != NULL) {
    strcpy(pszName, "Rectangle");
  }
}

DLL_EXPORT PainterFactory *PainterFactoryInstance() {
  PainterFactory *painterFactory = new RectanglePainterFactory;
  return painterFactory;
}

DLL_EXPORT QIcon *getPluginIcon() { return new QIcon(QString(":/rectangle/rectangle.png")); }
