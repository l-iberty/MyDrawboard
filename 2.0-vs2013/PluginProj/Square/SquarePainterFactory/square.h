#ifndef SQUARE_H
#define SQUARE_H

#include "../../Common/shape.h"

class MySquare :public Shape {
public:
    MySquare();
    ~MySquare();
    bool contains(QPoint &point) override;
    void setModel(QPoint &pt1, QPoint &pt2) override;
};

#endif // SQUARE_H
