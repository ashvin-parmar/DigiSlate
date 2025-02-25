#include "shapes_header/polygonshape.h"
int PolygonShape::count=1;
PolygonShape::PolygonShape(QObject *parent):Drawing(parent)
{
    this->penColor=Qt::black;
    this->brush=QBrush(Qt::white,Qt::SolidPattern);
    this->number=count++;
}
PolygonShape::~PolygonShape()
{

}
void PolygonShape::draw(QPainter &painter)
{
    if(this->points.size()>2)
    {
        painter.setPen(QPen(penColor,penWidth));
        painter.setBrush(brush);
        painter.drawPolygon(points,Qt::FillRule::WindingFill);
    }
}
void PolygonShape::clear()
{

}
QString PolygonShape::toString()
{
    return QString("Polygon")+QString::number(number);
}
void PolygonShape::select(QPainter &painter)
{

}
bool PolygonShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
}
QVector<QPoint> PolygonShape::getPoints() const
{
    return points;
}

void PolygonShape::setPoints(const QVector<QPoint> &value)
{
    points = value;
}
void PolygonShape::addPoint(const QPoint &point)
{
    this->points.append(point);
}
int PolygonShape::getPenWidth() const
{
    return penWidth;
}

void PolygonShape::setPenWidth(int value)
{
    penWidth = value;
}

QColor PolygonShape::getPenColor() const
{
    return penColor;
}

void PolygonShape::setPenColor(const QColor &value)
{
    penColor = value;
}

QBrush PolygonShape::getBrush() const
{
    return brush;
}

void PolygonShape::setBrush(const QBrush &value)
{
    brush = value;
}
