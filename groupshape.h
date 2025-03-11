#ifndef GROUPSHAPE_H
#define GROUPSHAPE_H

#include<drawing.h>
#include<QSet>
class GroupShape
{
public:
    GroupShape();
    ~GroupShape();
    void addShape(Drawing *shape);
    void removeShape(Drawing *shape);
    void removeAllShape();
    bool containShape(Drawing *shape);
    QSet<Drawing *> getShapes() const;
    int getCount() const;
private:
    QList<Drawing *> groupedShapes;
};

#endif // GROUPSHAPE_H
