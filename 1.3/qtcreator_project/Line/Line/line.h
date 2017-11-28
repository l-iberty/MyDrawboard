#ifndef LINE_H
#define LINE_H

#include "line_global.h"
#include "..\..\Common\shape.h"

// 直线方程 Ax+By+C=0 的参数
typedef struct {
    double A;
    double B;
    double C;
} LINEARGS, *PLINEARGS;

class Line :public Shape {
private:
    LINEARGS args;
    void getArgs(PLINEARGS pArgs);

public:
    Line();
    ~Line();

    void draw(QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    QString getDllModName() override;
};

#endif // LINE_H
