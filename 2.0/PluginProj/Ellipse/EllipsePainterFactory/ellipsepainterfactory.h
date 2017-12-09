#ifndef ELLIPSEPAINTERFACTORY_H
#define ELLIPSEPAINTERFACTORY_H

#include "../../Common/painterfactory.h"
#include "ellipsepainter.h"

class EllipsePainterFactory: public PainterFactory {
public:
    EllipsePainterFactory();
    ~EllipsePainterFactory();
    Painter* createPainter() override;
};

#endif // ELLIPSEPAINTERFACTORY_H
