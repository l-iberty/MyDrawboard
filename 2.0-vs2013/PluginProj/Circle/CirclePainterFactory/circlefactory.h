#ifndef CIRCLEFACTORY_H
#define CIRCLEFACTORY_H

#include "../../Common/shapefactory.h"

class CircleFactory : public ShapeFactory {
public:
  CircleFactory();
  ~CircleFactory();
  Shape *createShape() override;
  Shape *createShape(Shape *shape) override;
};

#endif // CIRCLEFACTORY_H
