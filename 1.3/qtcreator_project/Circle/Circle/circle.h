#ifndef CIRCLE_H
#define CIRCLE_H

#include "circle_global.h"
#include "..\..\Common\shape.h"

class Circle :public Shape {
private:
    int centerX;
    int centerY;
    int r;

public:
    Circle();
    ~Circle();

    void setRect(QRect &rect) override;
    void draw(QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    QString getDllModName() override;
};

#endif // CIRCLE_H
