#ifndef PAINTER_FACTORY_H
#define PAINTER_FACTORY_H

#include "painter.h"
#include <Windows.h>

class PainterFactory {
public:
    PainterFactory();
    virtual ~PainterFactory();
    virtual Painter* createPainter() = 0;
private:
    QPolygon* getQPolygon();
    QPoint getMovingPoint();
};

#endif // PAINTER_FACTORY_H
