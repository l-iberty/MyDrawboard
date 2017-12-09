#ifndef CIRCLE_H
#define CIRCLE_H

#include "../../Common/shape.h"

class MyCircle :public Shape {
public:
    MyCircle();
    ~MyCircle();
    bool contains(QPoint &point) override;
    void setModel(QPoint &pt1, QPoint &pt2) override;
};

#endif // CIRCLE_H
