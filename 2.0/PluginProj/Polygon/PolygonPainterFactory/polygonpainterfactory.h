#ifndef POLYGONPAINTERFACTORY_H
#define POLYGONPAINTERFACTORY_H

#include "../../Common/painterfactory.h"
#include "polygonpainter.h"

class PolygonPainterFactory: public PainterFactory {
public:
    PolygonPainterFactory();
    ~PolygonPainterFactory();
    Painter* createPainter() override;
};

#endif // POLYGONPAINTERFACTORY_H
