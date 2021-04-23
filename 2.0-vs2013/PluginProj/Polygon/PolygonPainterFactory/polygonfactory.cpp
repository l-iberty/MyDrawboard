#include "polygonfactory.h"
#include "polygon.h"

PolygonFactory::PolygonFactory() {}

PolygonFactory::~PolygonFactory() {}

Shape *PolygonFactory::createShape() {
  Shape *shape = new MyPolygon;
  return shape;
}

Shape *PolygonFactory::createShape(Shape *shape) {
  Shape *shapeCpy = new MyPolygon;
  shapeCpy->setKeyPoints(shape->getKeyPoints());
  return shapeCpy;
}
