#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../../Common/shape.h"

class MyRectangle :public Shape {
public:
    MyRectangle();
    ~MyRectangle();
    bool contains(QPoint &point) override;
};

#endif // RECTANGLE_H
