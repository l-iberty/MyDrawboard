#ifndef SQUAREFACTORY_H
#define SQUAREFACTORY_H

#include "../../Common/shapefactory.h"

class SquareFactory :public ShapeFactory {
public:
    SquareFactory();
    ~SquareFactory();
    Shape* createShape() override;
    Shape* createShape(Shape *shape) override;
};

#endif // SQUAREFACTORY_H
