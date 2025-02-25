#include "shapes_header/freehandshape.h"
int FreeHandShape::count=1;
FreeHandShape::FreeHandShape(QObject *parent):Drawing(parent)
{
    this->color=Qt::black;
    this->penWidth=1;
    number=count++;
}
FreeHandShape::~FreeHandShape()
{

}
void FreeHandShape::draw(QPainter &painter)
{
    painter.setRenderHint(painter.Antialiasing);
    painter.setPen(QPen(color,penWidth/*,Qt::PenStyle::SolidLine,Qt::PenCapStyle::RoundCap,Qt::PenJoinStyle::RoundJoin*/));
    //    painter.setBrush(QBrush(Qt::green,Qt::BrushStyle::SolidPattern));
    painter.drawPolyline(drawPath);
}
void FreeHandShape::clear()
{

}
QString FreeHandShape::toString()
{
 return (QString("FreeHand")+QString::number(number));
}
void FreeHandShape::select(QPainter &painter)
{
    QPen pen=painter.pen();
    pen.setWidth(penWidth+5);
    painter.setPen(pen);
    painter.drawPoint(this->drawPath.front());
    painter.drawPoint(this->drawPath.back());
}
bool FreeHandShape::isPointInShapeRegion(const QPoint &point)
{
    if(drawPath.containsPoint(point,Qt::FillRule::OddEvenFill))
    {
        return true;
    }
    return false;
}
void FreeHandShape::addPoint(const QPoint &point)
{
    this->drawPath.append(point);
}
int FreeHandShape::pathSize() const
{
    return this->drawPath.size();
}

QColor FreeHandShape::getColor() const
{
    return color;
}

void FreeHandShape::setColor(const QColor &value)
{
    color = value;
}

int FreeHandShape::getPenWidth() const
{
    return penWidth;
}

void FreeHandShape::setPenWidth(int value)
{
    penWidth = value;
}
