#include "shapes_header/pointshape.h"
int PointShape::count=1;
PointShape::PointShape(QObject *parent):Drawing(parent),penColor(Qt::black),penWidth(1)
{
x=0;
y=0;
number=count++;
}
PointShape::~PointShape()
{

}
void PointShape::draw(QPainter &painter)
{
painter.setPen(QPen(penColor,penWidth));
painter.drawPoint(x,y);
}
void PointShape::clear()
{

}
QString PointShape::toString()
{
    return QString("Point")+QString::number(number);
}
void PointShape::select(QPainter &painter)
{

}
bool PointShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
}
int PointShape::getX() const
{
    return x;
}

void PointShape::setX(int value)
{
    x = value;
}

int PointShape::getY() const
{
    return y;
}

void PointShape::setY(int value)
{
    y = value;
}

QColor PointShape::getPenColor() const
{
    return penColor;
}

void PointShape::setPenColor(const QColor &value)
{
    penColor = value;
}

int PointShape::getPenWidth() const
{
    return penWidth;
}

void PointShape::setPenWidth(int value)
{
    penWidth = value;
}
