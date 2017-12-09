#ifndef POLYGON_FACTORY_H
#define POLYGON_FACTORY_H

#include "../../Common/shapefactory.h"

class PolygonFactory :public ShapeFactory {
public:
    PolygonFactory();
    ~PolygonFactory();
    Shape* createShape() override;
    Shape* createShape(Shape *shape) override;
};

#endif // POLYGON_FACTORY_H
