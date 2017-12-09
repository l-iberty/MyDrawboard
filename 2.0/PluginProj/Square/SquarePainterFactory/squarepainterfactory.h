#ifndef SQUAREPAINTERFACTORY_H
#define SQUAREPAINTERFACTORY_H

#include "../../Common/painterfactory.h"
#include "squarepainter.h"

class SquarePainterFactory: public PainterFactory {
public:
    SquarePainterFactory();
    ~SquarePainterFactory();
    Painter* createPainter() override;
};

#endif // SQUAREPAINTERFACTORY_H
