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
    void drag(QMouseEvent *evt, QPaintDevice *device) override;
    bool contains(QPoint &point) override;
    void setKeyP1(QPoint &point) override;
    void setKeyP2(QPoint &point) override;
    void setP1(QPoint &point) override;
    void setP2(QPoint &point) override;
};

#endif // LINE_H
