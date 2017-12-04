#ifndef SHAPE_H
#define SHAPE_H
#include <QtGui/QPainter>
#include <QtGui/QtEvents>

class Shape {
public:
    Shape();
    virtual ~Shape();
    virtual QVector<QPoint> getKeyPoints();
    virtual void setKeyPoints(QVector<QPoint> &keyPoints);
    virtual void updateKeyPoints(int index, QPoint& point);
    virtual void removeLastKeyPoints();
    virtual void addKeyPoints(QMouseEvent *evt);
    virtual void addKeyPoints(QPoint &point);
    virtual void clearKeyPoints();
    virtual void setModel(QRect &model);
    virtual bool contains(QPoint &point) = 0;
protected:
    QRegion m_Region;
    QRect m_Model;
    QVector<QPoint> m_KeyPoints;
};

#endif // SHAPE_H
