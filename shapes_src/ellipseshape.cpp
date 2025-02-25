#include "shapes_header/ellipseshape.h"
int EllipseShape::count=1;
EllipseShape::EllipseShape(QObject *parent):Drawing(parent),penWidth(1)
{
    this->penColor=Qt::black;
    this->brush=QBrush(Qt::white,Qt::SolidPattern);
    this->isCenter=true;
    this->number=count++;
}
EllipseShape::~EllipseShape()
{

}

void EllipseShape::draw(QPainter &painter)
{
painter.setPen(QPen(penColor,penWidth));
painter.setBrush(brush);
if(isCenter) painter.drawEllipse(QPoint(x,y),horizontalRadius,verticalRadius);
else painter.drawEllipse(x,y,horizontalRadius*2,verticalRadius*2);
}
void EllipseShape::clear()
{

}
QString EllipseShape::toString()
{
    return (QString("Ellipse")+QString::number(number));
}
void EllipseShape::select(QPainter &painter)
{

}
bool EllipseShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
}
int EllipseShape::getX() const
{
    return x;
}

void EllipseShape::setX(int value)
{
    x = value;
}

int EllipseShape::getY() const
{
    return y;
}

void EllipseShape::setY(int value)
{
    y = value;
}

int EllipseShape::getHorizontalRadius() const
{
    return horizontalRadius;
}

void EllipseShape::setHorizontalRadius(int value)
{
    horizontalRadius = value;
}

int EllipseShape::getVerticalRadius() const
{
    return verticalRadius;
}

void EllipseShape::setVerticalRadius(int value)
{
    verticalRadius = value;
}

int EllipseShape::getPenWidth() const
{
    return penWidth;
}

void EllipseShape::setPenWidth(int value)
{
    penWidth = value;
}

QColor EllipseShape::getPenColor() const
{
    return penColor;
}

void EllipseShape::setPenColor(const QColor &value)
{
    penColor = value;
}

QBrush EllipseShape::getBrush() const
{
    return brush;
}

void EllipseShape::setBrush(const QBrush &value)
{
    brush = value;
}

bool EllipseShape::getIsCenter() const
{
    return isCenter;
}

void EllipseShape::setIsCenter(bool value)
{
    isCenter = value;
}
