#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "../../Common/shape.h"

class MyEllipse :public Shape {
public:
    MyEllipse();
    ~MyEllipse();
    bool contains(QPoint &point) override;
};

#endif // ELLIPSE_H
