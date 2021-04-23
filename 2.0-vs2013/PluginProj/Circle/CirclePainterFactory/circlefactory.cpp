#include "circlefactory.h"
#include "circle.h"

CircleFactory::CircleFactory() {}

CircleFactory::~CircleFactory() {}

Shape *CircleFactory::createShape() {
  Shape *shape = new MyCircle;
  return shape;
}

Shape *CircleFactory::createShape(Shape *shape) {
  Shape *shapeCpy = new MyCircle;
  shapeCpy->setKeyPoints(shape->getKeyPoints());
  return shapeCpy;
}
