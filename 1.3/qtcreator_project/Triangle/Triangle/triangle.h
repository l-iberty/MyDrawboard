#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "triangle_global.h"
#include "..\..\Common\shape.h"

class Triangle :public Shape {
private:
    QPolygon *triangle;

public:
    Triangle();
    ~Triangle();

    void draw(QPaintDevice *device) override;
    void addKeyPoints(QMouseEvent *evt) override;
    void addKeyPoints(QPoint &point) override;
    bool contains(QPoint &point) override;
    QString getDllModName() override;
};

#endif // TRIANGLE_H
