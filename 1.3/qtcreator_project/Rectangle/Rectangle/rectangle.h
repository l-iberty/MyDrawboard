#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "rectangle_global.h"
#include "..\..\Common\shape.h"

class Rectangle :public Shape {
public:
    Rectangle();
    ~Rectangle();

    void draw(QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    QString getDllModName() override;
};

#endif // RECTANGLE_H
