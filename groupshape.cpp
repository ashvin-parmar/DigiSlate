#include "groupshape.h"

GroupShape::GroupShape()
{

}
GroupShape::~GroupShape()
{
    groupedShapes.clear();
}
void GroupShape::addShape(Drawing *shape)
{
    if(shape) groupedShapes.append(shape);
}
void GroupShape::removeShape(Drawing *shape)
{
    if(shape) groupedShapes.removeOne(shape);
}
void GroupShape::removeAllShape()
{
    this->groupedShapes.clear();
}
bool GroupShape::containShape(Drawing *shape)
{
    return this->groupedShapes.contains(shape);
}
QSet<Drawing *> GroupShape::getShapes() const
{
    return QSet<Drawing *>(this->groupedShapes.begin(),this->groupedShapes.end());
}
int GroupShape::getCount() const
{
    return this->groupedShapes.size();
}
