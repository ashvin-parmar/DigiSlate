#include "shapes_header/roundedrectangleshape.h"
int RoundedRectangleShape::count=1;
RoundedRectangleShape::RoundedRectangleShape(QObject *parent):Drawing(parent),penWidth(1)
{
    this->penColor=Qt::black;
    this->brush=QBrush(Qt::white,Qt::SolidPattern);
    this->x=100;
    this->y=100;
    this->width=100;
    this->height=100;
    this->xRadius=0;
    this->yRadius=0;
    this->number=count++;
}
RoundedRectangleShape::~RoundedRectangleShape()
{

}
void RoundedRectangleShape::draw(QPainter &painter)
{
    painter.setPen(QPen(penColor,penWidth));
    painter.setBrush(brush);
    painter.drawRoundedRect(x,y,width,height,xRadius,yRadius,Qt::SizeMode::AbsoluteSize);
}
void RoundedRectangleShape::clear()
{

}
QString RoundedRectangleShape::toString()
{
    return QString("RoundedRectangle")+QString::number(number);
}
void RoundedRectangleShape::select(QPainter &painter)
{

}
bool RoundedRectangleShape::isPointInShapeRegion(const QPoint &point)
{
   Q_UNUSED(point);
    return false;
}
int RoundedRectangleShape::getX() const
{
    return x;
}
void RoundedRectangleShape::setX(int value)
{
    x = value;
}

int RoundedRectangleShape::getY() const
{
    return y;
}

void RoundedRectangleShape::setY(int value)
{
    y = value;
}

int RoundedRectangleShape::getWidth() const
{
    return width;
}

void RoundedRectangleShape::setWidth(int value)
{
    width = value;
}

int RoundedRectangleShape::getHeight() const
{
    return height;
}

void RoundedRectangleShape::setHeight(int value)
{
    height = value;
}

int RoundedRectangleShape::getXRadius() const
{
    return xRadius;
}

void RoundedRectangleShape::setXRadius(int value)
{
    xRadius = value;
}

int RoundedRectangleShape::getYRadius() const
{
    return yRadius;
}

void RoundedRectangleShape::setYRadius(int value)
{
    yRadius = value;
}

QColor RoundedRectangleShape::getPenColor() const
{
    return penColor;
}

void RoundedRectangleShape::setPenColor(const QColor &value)
{
    penColor = value;
}

QBrush RoundedRectangleShape::getBrush() const
{
    return brush;
}

void RoundedRectangleShape::setBrush(const QBrush &value)
{
    brush = value;
}

int RoundedRectangleShape::getPenWidth() const
{
    return penWidth;
}

void RoundedRectangleShape::setPenWidth(int value)
{
    penWidth = value;
}
