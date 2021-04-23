#include "squarefactory.h"
#include "square.h"

SquareFactory::SquareFactory() {}

SquareFactory::~SquareFactory() {}

Shape *SquareFactory::createShape() {
  Shape *shape = new MySquare;
  return shape;
}

Shape *SquareFactory::createShape(Shape *shape) {
  Shape *shapeCpy = new MySquare;
  shapeCpy->setKeyPoints(shape->getKeyPoints());
  return shapeCpy;
}
