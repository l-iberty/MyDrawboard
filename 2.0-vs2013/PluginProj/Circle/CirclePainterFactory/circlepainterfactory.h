#ifndef CIRCLEPAINTERFACTORY_H
#define CIRCLEPAINTERFACTORY_H

#include "../../Common/painterfactory.h"
#include "circlepainter.h"

class CirclePainterFactory: public PainterFactory {
public:
    CirclePainterFactory();
    ~CirclePainterFactory();
    Painter* createPainter() override;
};

#endif // CIRCLEPAINTERFACTORY_H
