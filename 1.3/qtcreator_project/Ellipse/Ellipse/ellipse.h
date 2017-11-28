#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "ellipse_global.h"
#include "..\..\Common\shape.h"

class Ellipse :public Shape {
public:
    Ellipse();
    ~Ellipse();

    void draw(QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    QString getDllModName() override;
};

#endif // ELLIPSE_H
