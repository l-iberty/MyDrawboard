#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include "shape.h"
#include <Windows.h>

class ShapeFactory {
public:
  ShapeFactory();
  virtual ~ShapeFactory();
  virtual Shape *createShape() = 0;
  virtual Shape *createShape(Shape *shape) = 0;
};

#endif // SHAPE_FACTORY_H
