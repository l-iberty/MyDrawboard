#ifndef ARC_H
#define ARC_H

#include "arc_global.h"
#include "../../Common/shape.h"

class Arc: public Shape {

public:
    Arc();
    ~Arc();

    void draw(QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    QString getDllModName() override;
};

#endif // ARC_H
