#include "rectanglefactory.h"
#include "rectangle.h"

RectangleFactory::RectangleFactory() {}

RectangleFactory::~RectangleFactory() {}

Shape *RectangleFactory::createShape() {
  Shape *shape = new MyRectangle;
  return shape;
}

Shape *RectangleFactory::createShape(Shape *shape) {
  Shape *shapeCpy = new MyRectangle;
  shapeCpy->setKeyPoints(shape->getKeyPoints());
  return shapeCpy;
}
