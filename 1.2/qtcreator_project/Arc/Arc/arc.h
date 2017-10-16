#ifndef ARC_H
#define ARC_H

#include "arc_global.h"
#include "../../Common/shape.h"

class Arc: public Shape {

public:
    Arc();
    ~Arc();

    void setRect() override;
    void draw(QPaintDevice *device) override;
    void drag(QMouseEvent *evt, QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    void addKeyPoints(QMouseEvent *evt) override;
    void addKeyPoints(QPoint &point) override;
    void clearKeyPoints() override;
    void setP1(QPoint &point) override;
    void setP2(QPoint &point) override;
    QString getDllModName() override;
};

#endif // ARC_H
