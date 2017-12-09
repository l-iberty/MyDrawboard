#ifndef SQUAREPAINTER_H
#define SQUAREPAINTER_H

#include "square.h"
#include "squarefactory.h"
#include "../../Common/painter.h"

class SquarePainter :public MySquare, public Painter {
public:
    SquarePainter();
    ~SquarePainter();
    void getFactoryFileName(char *pszFileName) override;
    void handleMouseMovePoint(QMouseEvent *evt) override;
    void handleMousePressPoint(QPoint &point) override;
    void draw(QPaintDevice *device) override;
    void draw(Shape *shape, QPaintDevice *device) override;
};

#endif // SQUAREPAINTER_H
