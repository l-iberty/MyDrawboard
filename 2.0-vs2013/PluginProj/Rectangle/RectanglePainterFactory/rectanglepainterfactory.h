#ifndef RECTANGLEPAINTERFACTORY_H
#define RECTANGLEPAINTERFACTORY_H

#include "../../Common/painterfactory.h"
#include "rectanglepainter.h"

class RectanglePainterFactory : public PainterFactory {
public:
  RectanglePainterFactory();
  ~RectanglePainterFactory();
  Painter *createPainter() override;
};

#endif // RECTANGLEPAINTERFACTORY_H
