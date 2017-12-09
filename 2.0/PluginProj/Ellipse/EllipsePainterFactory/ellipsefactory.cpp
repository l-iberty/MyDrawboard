#include "ellipsefactory.h"
#include "ellipse.h"

EllipseFactory::EllipseFactory() {

}

EllipseFactory::~EllipseFactory() {

}

Shape* EllipseFactory::createShape() {
    Shape *shape = new MyEllipse;
    return shape;
}

Shape* EllipseFactory::createShape(Shape *shape) {
    Shape *shapeCpy = new MyEllipse;
    shapeCpy->setKeyPoints(shape->getKeyPoints());
    return shapeCpy;
}
