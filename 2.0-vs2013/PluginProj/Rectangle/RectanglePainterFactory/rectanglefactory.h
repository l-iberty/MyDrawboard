#ifndef RECTANGLEFACTORY_H
#define RECTANGLEFACTORY_H

#include "../../Common/shapefactory.h"

class RectangleFactory : public ShapeFactory {
public:
  RectangleFactory();
  ~RectangleFactory();
  Shape *createShape() override;
  Shape *createShape(Shape *shape) override;
};

#endif // RECTANGLEFACTORY_H
