#ifndef ELLIPSEFACTORY_H
#define ELLIPSEFACTORY_H

#include "../../Common/shapefactory.h"

class EllipseFactory : public ShapeFactory {
public:
  EllipseFactory();
  ~EllipseFactory();
  Shape *createShape() override;
  Shape *createShape(Shape *shape) override;
};

#endif // ELLIPSEFACTORY_H
