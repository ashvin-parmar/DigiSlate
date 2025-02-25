#include "shapes_header/polylineshape.h"
int PolylineShape::count=1;
PolylineShape::PolylineShape(QObject *parent):Drawing(parent),penWidth(1)
{
this->penColor=Qt::black;
this->brush=QBrush(Qt::white,Qt::SolidPattern);
this->number=count++;
}
PolylineShape::~PolylineShape()
{

}
void PolylineShape::draw(QPainter &painter)
{
    if(this->points.size()>1)
    {
        painter.setPen(QPen(penColor,penWidth));
        painter.setBrush(brush);
        painter.drawPolyline(points);
    }
}
void PolylineShape::clear()
{

}
QString PolylineShape::toString()
{
    return QString("Polyline")+QString::number(number);
}
void PolylineShape::select(QPainter &painter)
{

}
bool PolylineShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
}
QVector<QPoint> PolylineShape::getPoints() const
{
    return points;
}

void PolylineShape::setPoints(const QVector<QPoint> &value)
{
    points = value;
}
void PolylineShape::addPoint(const QPoint &point)
{
    this->points.append(point);
}

int PolylineShape::getPenWidth() const
{
    return penWidth;
}

void PolylineShape::setPenWidth(int value)
{
    penWidth = value;
}

QColor PolylineShape::getPenColor() const
{
    return penColor;
}

void PolylineShape::setPenColor(const QColor &value)
{
    penColor = value;
}

QBrush PolylineShape::getBrush() const
{
    return brush;
}

void PolylineShape::setBrush(const QBrush &value)
{
    brush = value;
}
